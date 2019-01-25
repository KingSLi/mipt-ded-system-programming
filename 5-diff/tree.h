#ifndef INC_5_DIFF_TREE_H
#define INC_5_DIFF_TREE_H

#include <vector>
#include <memory>


enum class TypeNode{
  ADD, // start binary
  SUB,
  MUL,
  DIV,
  POW,
  MINUS, // start unary
  LOG,
  SIN,
  COS,
  NUMBER, // special operation
  VARIABLE,
  OPEN_BRACE
};

struct Node{
  std::shared_ptr<Node> left_{nullptr};
  std::shared_ptr<Node> right_{nullptr};
  TypeNode type_;
  double value_{0};

  Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right, TypeNode type, double value=0) : left_(left),
                                                                     right_(right),
                                                                     type_(type),
                                                                     value_(value) {}
};

using NodePtr =  std::shared_ptr<Node>;

NodePtr create_ptr(Node node) {
  return std::make_shared<Node>(node);
}

NodePtr differentiation(const NodePtr& root) {
  if (root == nullptr) {
    return nullptr;
  }
  auto diff_left = differentiation(root->left_);
  auto diff_right = differentiation(root->right_);
  switch (root->type_) {
    case TypeNode::ADD:{
      auto answer = create_ptr({diff_left, diff_right, TypeNode::ADD});
      return answer;
    }
    case TypeNode::SUB:{
      auto answer = create_ptr({diff_left, diff_right, TypeNode::SUB});
      return answer;
    }
    case TypeNode::MUL : {
      auto tmp1 = create_ptr({diff_left, root->right_, TypeNode::MUL});
      auto tmp2 = create_ptr({root->left_, diff_right, TypeNode::MUL});
      auto answer =  create_ptr({tmp1, tmp2, TypeNode::ADD});
      return answer;
    }
    case TypeNode::DIV : {
      auto tmp1 = create_ptr({diff_left, root->right_, TypeNode::MUL});
      auto tmp2 = create_ptr({root->left_, diff_right, TypeNode::MUL});
      auto numerator =  create_ptr({tmp1, tmp2, TypeNode::SUB});
      auto denominator = create_ptr({root->right_,
                                     create_ptr({nullptr, nullptr, TypeNode::NUMBER, 2}),
                                     TypeNode::POW});
      auto answer = create_ptr({numerator, denominator, TypeNode::DIV});
      return answer;
    }
    case TypeNode::POW : {
      if (root->right_->type_ == TypeNode::NUMBER) {
        auto tmp1 = create_ptr({root->left_,
                                create_ptr({nullptr, nullptr, TypeNode::NUMBER, root->right_->value_ - 1}),
                                TypeNode::POW});
        auto tmp2 = create_ptr({create_ptr({nullptr, nullptr, TypeNode::NUMBER, root->right_->value_}),
                                tmp1,
                                TypeNode::MUL});
        auto answer = create_ptr({tmp2, diff_left, TypeNode::MUL});
        return answer;
      }
      // f(x) = h(x)^g(x)
      // f'(x) = f(x) * (g(x)*ln(h(x)))'
      auto tmp1 = create_ptr({root->right_,
                              create_ptr({nullptr, root->left_, TypeNode::LOG}),
                              TypeNode::MUL});
      auto answer = create_ptr({root,
                                differentiation(tmp1),
                                TypeNode::MUL});
      return answer;
    }
    case TypeNode::MINUS: {
      auto answer = create_ptr({nullptr, diff_right, TypeNode::MINUS});
      return answer;
    }
    case TypeNode::SIN : {
      auto tmp = create_ptr({nullptr, root->right_, TypeNode::COS});
      auto answer = create_ptr({tmp, diff_right, TypeNode ::MUL});
      return answer;
    }

    case TypeNode::COS : {
      auto tmp = create_ptr({nullptr, root->right_, TypeNode ::SIN});
      auto minus_tmp = create_ptr({nullptr, tmp, TypeNode::MINUS});
      auto answer = create_ptr({minus_tmp, diff_right, TypeNode ::MUL});
      return answer;
    }

    case TypeNode::LOG : {
      auto tmp =  create_ptr({create_ptr({nullptr, nullptr, TypeNode ::NUMBER, 1}),
                                         root->right_,
                                         TypeNode::DIV});
      auto answer = create_ptr({tmp, diff_right, TypeNode::MUL});
      return answer;
    }

    case TypeNode::VARIABLE : {
      auto answer = create_ptr({nullptr, nullptr, TypeNode ::NUMBER, 1});
      return answer;
    }
    case TypeNode::NUMBER : {
      auto answer = create_ptr({nullptr, nullptr, TypeNode ::NUMBER, 0});
      return answer;
    }
    default: return nullptr;
  }
}

#endif //INC_5_DIFF_TREE_H


