#ifndef INC_5_DIFF_PARSEER_HPP
#define INC_5_DIFF_PARSEER_HPP

#include "tree.h"

bool is_op (char c) {
  return c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='c' || c=='s' || c=='l';
}

TypeNode detect_operation(char c) {
  switch (c) {
    case '+': return TypeNode::ADD;
    case '-': return TypeNode::SUB;
    case '*': return TypeNode::MUL;
    case '/': return TypeNode::DIV;
    case '^': return TypeNode::POW;
    case 'c': return TypeNode::COS;
    case 's': return TypeNode::SIN;
    case 'l': return TypeNode::LOG;
  }
}

int priority (TypeNode op) {
  if (op == TypeNode::OPEN_BRACE)
    return 0;
  if (op == TypeNode::ADD || op == TypeNode::SUB)
    return 1;
  if (op == TypeNode::MUL || op == TypeNode::DIV)
    return 2;
  if (op == TypeNode::POW)
    return 3;
  if (op == TypeNode::MINUS)
    return 5;
  return 4; // for log, exp, pow, cos, sin
}

void process_op (std::vector<NodePtr> & st, TypeNode op) {
  if (op >= TypeNode::MINUS) { // unary
    auto operand = st.back();
    st.pop_back();
    auto ans =  create_ptr({nullptr, operand, op});
    st.push_back(ans);
  } else {
    auto r = st.back();  st.pop_back();
    auto l = st.back();  st.pop_back();
    auto ans =  create_ptr({l, r, op});
    st.push_back(ans);
  }
}

NodePtr parse_expression(std::string& s) {
  bool may_unary = true;
  std::vector<NodePtr> st;
  std::vector<TypeNode> op;
  for (size_t i=0; i<s.length(); ++i) {
    if (s[i] == ' ') {
      continue;
    } else if (s[i] == '(') {
      op.push_back (TypeNode::OPEN_BRACE);
      may_unary = true;
    } else if (s[i] == ')') {
      while (op.back() != TypeNode::OPEN_BRACE) {
        process_op(st, op.back());
        op.pop_back();
      }
      op.pop_back();
      may_unary = false;
    } else if (is_op (s[i])) {
      TypeNode cur_op = detect_operation(s[i]);
      if (may_unary && cur_op == TypeNode::SUB)
        cur_op = TypeNode::MINUS;
      while (!op.empty() && (
              cur_op < TypeNode::MINUS && priority(op.back()) >= priority(cur_op)
              || cur_op >= TypeNode::MINUS && priority(op.back()) > priority(cur_op))
              )
        process_op (st, op.back()),  op.pop_back();
      op.push_back (cur_op);
      may_unary = true;
      if (cur_op > TypeNode::MINUS)
        i += 2;
    } else {
      std::string operand;
      while (i < s.length() && isalnum (s[i]))
      operand += s[i++];
      --i;
      if (isdigit (operand[0]))
        st.push_back ( create_ptr({nullptr, nullptr, TypeNode::NUMBER, atoi (operand.c_str())}));
      else
        st.push_back ( create_ptr({nullptr, nullptr, TypeNode::VARIABLE}));
      may_unary = false;
    }
  }
  while (!op.empty())
    process_op (st, op.back()),  op.pop_back();
  return st.back();
}

#endif //INC_5_DIFF_PARSEER_HPP
