#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <cassert>
#include "GlobalVariableAction.h"

using namespace globalVariable;
using namespace clang;
using namespace clang::tooling;

static clang::FrontendPluginRegistry::Add<GlobalVariableAction>
    X("global_variable", "Generate error message if file includes a variable that has global storage");

class VariableVisitor : public clang::RecursiveASTVisitor<VariableVisitor>
{
public:
    VariableVisitor(const ASTContext *context) : m_context(context)
    {
        assert(context);
    }
    bool VisitVarDecl(clang::VarDecl *v)
    {
        assert(v);
        const std::string &varName = v->getQualifiedNameAsString();
        const SourceManager& mgr = m_context->getSourceManager();
        if (!mgr.isInSystemHeader(v->getSourceRange().getBegin()))
        {
            if (v->hasGlobalStorage())
            {
                const auto srcLoc = mgr.getFileLoc(v->getSourceRange().getBegin());
                llvm::errs() << "Error: Variable " << varName << " at " << srcLoc.printToString(mgr) <<" has global storage. This is not permitted by the instructor"
                             << "\n";
            }
        }
        return true;
    }

private:
    const ASTContext *m_context;
};

void GlobalVariableAction::EndSourceFileAction()
{
    auto &ci = getCompilerInstance();
    auto &context = ci.getASTContext();

    auto &input = getCurrentInput();
    llvm::StringRef fileName = input.getFile();
    //llvm::outs() << "Filename in Action: " << fileName << "\n";

    auto *unit = context.getTranslationUnitDecl();
    VariableVisitor visitor{&context};
    visitor.TraverseDecl(unit);
    clang::ASTFrontendAction::EndSourceFileAction();
}
