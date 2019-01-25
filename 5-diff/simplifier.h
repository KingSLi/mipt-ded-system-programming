#ifndef INC_5_DIFF_SIMPLIFIER_H
#define INC_5_DIFF_SIMPLIFIER_H

#include "tree.h"

void simplify(NodePtr& root) {
  if (root == nullptr) {
    return;
  }
  simplify(root->left_);
  simplify(root->right_);
  switch (root->type_) {
    case TypeNode::ADD:{
      if (root->left_->type_ == TypeNode::NUMBER && root->left_->value_ == 0)
        root = root->right_;
      else if (root->right_->type_ == TypeNode::NUMBER && root->right_->value_ == 0)
        root = root->left_;
      else if (root->right_->type_ == TypeNode::MINUS) {
        root->right_ = root->right_->right_;
        root->type_ = TypeNode::SUB;
      }
      break;
    }
    case TypeNode::SUB:{
      if (root->left_->type_ == TypeNode::NUMBER && root->left_->value_ == 0)
        root = create_ptr({nullptr, root->right_, TypeNode::MINUS});
      else if (root->right_->type_ == TypeNode::NUMBER && root->right_->value_ == 0)
        root = root->left_;
      else if (root->right_->type_ == TypeNode::MINUS) {
        root->right_ = root->right_->right_;
        root->type_ = TypeNode::ADD;
      }
      break;
    }
    case TypeNode::MUL : {
      if (root->left_->type_ == TypeNode::NUMBER) {
        if (root->left_->value_ == 1)
          root = root->right_;
        else if (root->left_->value_ == 0)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 0});
      } else if (root->right_->type_ == TypeNode::NUMBER) {
        if (root->right_->value_ == 1)
          root = root->left_;
        else if (root->right_->value_ == 0)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 0});
      }
      break;
    }
    case TypeNode::DIV : {
      if (root->left_->type_ == TypeNode::NUMBER) {
        if (root->left_->value_ == 0)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 0});
      } else if (root->right_->type_ == TypeNode::NUMBER) {
        if (root->right_->value_ == 1)
          root = root->left_;
      }
      break;
    }
    case TypeNode::POW : {
      if (root->left_->type_ == TypeNode::NUMBER) {
        if (root->left_->value_ == 1)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 1});
        else if (root->left_->value_ == 0)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 0});
      } else if (root->right_->type_ == TypeNode::NUMBER) {
        if (root->right_->value_ == 1)
          root = root->left_;
        else if (root->right_->value_ == 0)
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 1});
      }
      break;
    }
    case TypeNode::MINUS: {
      if (root->right_->type_ == TypeNode::NUMBER && root->right_->value_ == 0) {
          root = create_ptr({nullptr, nullptr, TypeNode::NUMBER, 0});
      }
      break;
    }
  }
}

#endif //INC_5_DIFF_SIMPLIFIER_H
