

#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <cassert>
#include "RecursiveFunctionsAction.h"

using namespace recursiveFunctions;
using namespace clang;
using namespace clang::tooling;

static clang::FrontendPluginRegistry::Add<RecursiveFunctionsAction>
    X("recursive_functions", "Generate error message if file contains no recursive functions");

namespace
{
  bool recursiveFuncFound = false;
}

class FunctionNameVisitor : public clang::RecursiveASTVisitor<FunctionNameVisitor>
{
public:
  FunctionNameVisitor(const ASTContext *context) : m_context(context)
  {
    assert(context);
  }
  bool
  VisitFunctionDecl(clang::FunctionDecl *f)
  {
    assert(f);
    caller = f;
    return true;
  }
  bool VisitCallExpr(CallExpr *CallExpression)
  {
    QualType q = CallExpression->getType();
    const Type *t = q.getTypePtrOrNull();

    if (t != NULL)
    {
      FunctionDecl *func = CallExpression->getDirectCallee();
      if (func)
      {
        const std::string funcName = func->getQualifiedNameAsString();
        if (!m_context->getSourceManager().isInSystemHeader(func->getSourceRange().getBegin()))
          recursiveFuncFound = recursiveFuncFound || (func == caller);
      }
    }

    return true;
  }

private:
  FunctionDecl *caller;
  const ASTContext *m_context;
};

bool RecursiveFunctionsAction::ParseArgs(const clang::CompilerInstance &ci,
                                         const std::vector<std::string> &args)
{
  return true;
}

void RecursiveFunctionsAction::EndSourceFileAction()
{
  auto &ci = getCompilerInstance();
  auto &context = ci.getASTContext();

  auto &input = getCurrentInput();
  llvm::StringRef fileName = input.getFile();
  llvm::outs() << "Filename in Action: " << fileName << "\n";

  auto *unit = context.getTranslationUnitDecl();
  FunctionNameVisitor visitor{&context};
  visitor.TraverseDecl(unit);

  if (!recursiveFuncFound)
  {
    // unsigned id = ci.getDiagnostics().getDiagnosticIDs()->getCustomDiagID(DiagnosticIDs::Level::Error, "No recursive function found" );
    // DiagnosticBuilder B = ci.getDiagnostics().Report(id);
    // B.setForceEmit();
    llvm::errs() << "Error: No recursive function found !!"
                 << "\n";
  }
  clang::ASTFrontendAction::EndSourceFileAction();
}
