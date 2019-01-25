#ifndef INC_5_DIFF_PRINTER_H
#define INC_5_DIFF_PRINTER_H

std::string operator_to_str(TypeNode type) {
  switch (type) {
    case TypeNode::ADD:
      return " + ";
    case TypeNode::SUB:
      return " - ";
    case TypeNode::MUL:
      return " * ";
    case TypeNode::DIV:
      return " / ";
    case TypeNode::POW:
      return " ^ ";
    case TypeNode::LOG:
      return "Log";
    case TypeNode::COS:
      return "Cos";
    case TypeNode::SIN:
      return "Sin";
    case TypeNode::MINUS:
      return "-";
    default:
      return "";
  }
}

void print_expression(NodePtr root) {
  if (root->left_ != nullptr) {
    if (root->left_->type_ == TypeNode::ADD
        || root->left_->type_ == TypeNode::SUB
        || root->type_ == TypeNode::POW)
      std::cout << "(";
    print_expression(root->left_);
    if (root->left_->type_ == TypeNode::ADD
        || root->left_->type_ == TypeNode::SUB
        || root->type_ == TypeNode::POW)
      std::cout << ")";
  }

  if (root->type_ == TypeNode::NUMBER)
    std::cout << root->value_;
  else if (root->type_ == TypeNode::VARIABLE)
    std::cout << 'x';
  else if (root->type_ >= TypeNode::MINUS)
    std::cout << operator_to_str(root->type_) << "(";
  else std::cout << operator_to_str(root->type_);

  if (root->right_ != nullptr) {
    if (root->right_->type_ == TypeNode::ADD ||
        root->right_->type_ == TypeNode::SUB ||
        root->type_ == TypeNode::POW)
      std::cout << "(";
    print_expression(root->right_);
    if (root->right_->type_ == TypeNode::ADD ||
        root->right_->type_ == TypeNode::SUB ||
        root->type_ == TypeNode::POW)
      std::cout << ")";
  }

  if (root->type_ >= TypeNode::MINUS && root->type_ < TypeNode::NUMBER)
    std::cout << ")";
}

#endif //INC_5_DIFF_PRINTER_H
