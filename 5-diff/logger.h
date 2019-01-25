//#ifndef INC_5_DIFF_LOGGER_H
//#define INC_5_DIFF_LOGGER_H
//
//
//#pragma once
//
//#include <iostream>
//#include <fstream>
//#include <utility>
//#include <stdlib.h>
//#include "tree.h"
//
//class TexLogger {
// public:
//  explicit TexLogger(const std::string filename = "output.tex") : fout_(filename),
//                                                                  filename_(filename) {
//    fout_ << "\\documentclass[12pt]{article}" << std::endl;
//    fout_ << "\\usepackage[utf8x]{inputenc}" << std::endl;
//    fout_ << "\\usepackage[english,russian]{babel}" << std::endl;
//    fout_ << "\\usepackage{cmap}" << std::endl;
//    fout_ << std::endl;
//    fout_ << "\\begin{document}" << std::endl;
//  }
//
//  ~TexLogger() {
//    fout_ << "\\end{document}" << std::endl;
//    std::string to_call = "pdflatex " + filename_ + " > /dev/null";
//    system(to_call.c_str());
//  }
//
//  void WriteTreeToTex(node_t curr, std::string label = "", bool tex_label = false) {
//    if (tex_label) {
//      fout_ << "$" << label << ConvertTreeToString(curr) << "$" ;
//    } else {
//      fout_ << label << "$" << ConvertTreeToString(curr) << "$" ;
//    }
//  }
//
//  void WriteLine(std::string line) {
//    fout_ << line;
//  }
//
//  void WriteBinaryOperationDerivative(node_t operation, node_t derivative) {
//    fout_ << R"($\frac{\partial}{\partial x})";
//    fout_ << "(" << ConvertTreeToString(operation) << ") = ";
//    fout_ << ConvertTreeToString(derivative) << "$\n\n";
//  }
//
//  void WriteUnaryOperationDerivative(node_t operation, node_t derivative) {
//    fout_ << R"($\frac{\partial}{\partial x})";
//    fout_ << "(" << ConvertTreeToString(operation) << ") = ";
//    fout_ << ConvertTreeToString(derivative) << "$\n\n";
//  }
//
// private:
//  std::ofstream fout_;
//  std::string filename_;
//
// private:
//  std::string ConvertTreeToString(node_t curr) {
//    if (curr == nullptr) {
//      return "";
//    }
//    auto d_left = ConvertTreeToString(curr->left_);
//    auto d_right = ConvertTreeToString(curr->right_);
//    switch (curr->type_name_) {
//      case NodeTypeName::SUB:{
//        return d_left + "-" + d_right;
//      }
//      case NodeTypeName::ADD:{
//        return d_left + "+" + d_right;
//      }
//      case NodeTypeName::MUL : {
//        return d_left + "*" + d_right;
//      }
//      case NodeTypeName::DIV : {
//        return "\\frac{" + d_left + "}{" + d_right + "}";
//      }
//
//      case NodeTypeName::POW : {
//        return d_left + "^{" + d_right + "}";
//      }
//
//      case NodeTypeName::UNARY_MINUS : {
//        return "-" + d_left;
//      }
//
//      case NodeTypeName::SIN : {
//        return "sin(" + d_left + ")";
//      }
//
//      case NodeTypeName::COS : {
//        return "cos(" + d_left + ")";
//      }
//
//      case NodeTypeName::LOG : {
//        return "log(" + d_left + ")";
//      }
//
//      case NodeTypeName::VARIABLE : {
//        std::string ans = "";
//        ans.push_back((char)curr->value_);
//        return ans;
//      }
//
//      case NodeTypeName::NUMBER : {
//        return std::to_string(curr->value_);
//      }
//      default: return "";
//    }
//  }
//};
//
//#endif //INC_5_DIFF_LOGGER_H
