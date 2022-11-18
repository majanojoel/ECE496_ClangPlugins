#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <cassert>
#include "LibraryCatchAction.h"

using namespace libraryCatch;
using namespace clang;
using namespace clang::tooling;

static clang::FrontendPluginRegistry::Add<LibraryCatchAction>
  X("library_catch", "Generate error message if file includes a library that the instructor does not permit");

class ClassNameVisitor :
  public clang::RecursiveASTVisitor<ClassNameVisitor> {
public:

ClassNameVisitor(const std::vector<std::string> libraries) : 
    bannedLibraries(libraries)
{}

bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
  std::string className = Declaration->getQualifiedNameAsString();
  if (className.find("std") != std::string::npos){
        for(std::size_t i = 0 ; i < bannedLibraries.size() ; ++i)
        {
            if(className.find(bannedLibraries[i]) != std::string::npos)
            {
                llvm::errs() << "Error: library "<< bannedLibraries[i] <<" is not permitted by the instructor"<<"\n";
            }
        }

  }
  return true;
}
private:
    std::vector<std::string> bannedLibraries;
};

bool
  LibraryCatchAction::ParseArgs(const clang::CompilerInstance &ci,
            const std::vector<std::string>& args)
{
    bannedLibraries = args;
    return true;
}


void
LibraryCatchAction::EndSourceFileAction() {
  auto &ci      = getCompilerInstance();
  auto &context = ci.getASTContext();

  auto &input = getCurrentInput();
  llvm::StringRef fileName = input.getFile();
  llvm::outs() << "Filename in Action: " << fileName << "\n";

  auto *unit = context.getTranslationUnitDecl();
  ClassNameVisitor visitor(bannedLibraries);
  visitor.TraverseDecl(unit);
  clang::ASTFrontendAction::EndSourceFileAction();

}