
#pragma once

#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"

#include <memory>

namespace recursiveFunctions
{

  class RecursiveFunctionsAction : public clang::PluginASTAction
  {
  public:
    RecursiveFunctionsAction()
    {
    }

    std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef) override
    {
      ci.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());
      return std::make_unique<clang::ASTConsumer>();
    }

    bool
    ParseArgs(const clang::CompilerInstance &ci,
              const std::vector<std::string> &args) override;

  protected:
    void EndSourceFileAction() override;

    clang::PluginASTAction::ActionType
    getActionType() override
    {
      return ReplaceAction;
    }
  };
  std::vector<std::string> requiredRecursiveFunctions;

}
