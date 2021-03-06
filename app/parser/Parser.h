#ifndef PARSER_H
#define PARSER_H

#include "AppInfo.h"
#include "GenAPI.h"
#include "GenCodeText.h"
#include "GenExam.h"
#include "GenExams.h"
#include "GenHeader.h"
#include "GenImage.h"
#include "GenItem.h"
#include "GenLogicDiagramAON.h"
#include "GenLogicDiagramAOXN.h"
#include "GenLogicExprAON.h"
#include "GenLogicExprAOXN.h"
#include "GenNestedFor.h"
#include "GenOption.h"
#include "GenRandom.h"
#include "GenSelector.h"
#include "GenSolution.h"
#include "GenStem.h"
#include "GenText.h"
#include "GenTwoC.h"
#include "Log.h"
#include "RandomProfile.h"
#include "Reader.h"
#include "Util.h"

#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_escape_char.hpp>
#include <boost/spirit/include/classic_if.hpp>
#include <boost/spirit/include/classic_lists.hpp>
#include <boost/spirit/include/classic_symbols.hpp>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace bsc = boost::spirit::classic;

/// This structure contains all semantic actions of the parser.
/// @todo GenericFactory not used, replace?
struct ExamBuilder {
   // Errors to check for during the parse
   enum class ERROR {
      NO = 0,
      EXM_EXPECTED,
      CLOSING_BRACKET_EXPECTED,
      UNSIGNEDINT_EXPECTED,
      SEMICOLON_EXPECTED
   };

   ERROR error_{ERROR::NO};
   std::vector<Reader::message_t> &messages_;

   RandomProfile randomProfile;
   std::vector<std::shared_ptr<GenExams>> Product;
   int level_;
   GenHeader tempHeader{"_local_"};
   std::string type;
   std::string text;
   std::string lhs;
   std::string rhs;
   std::string id_;
   std::string itemScope;
   std::string examScope;
   std::shared_ptr<GenItem> p_actualItem;
   std::shared_ptr<GenHeader> p_actualHeader;
   std::string function_id;
   std::vector<std::string> parList;
   size_t par_;
   int actualOptionIndex;
   std::shared_ptr<GenOption> p_actualOption;
   bool isArrayElement_;

   bsc::symbols<std::string> vars_p;
   bsc::symbols<IGenPtr_t> generators_p;

   std::function<void(const char *, const char *)> errorMessage;
   std::function<void(const char *, const char *)> initText;
   std::function<void(const char)> addChar;
   std::function<void(const char *, const char *)> concatText;
   std::function<void(const char *, const char *)> addNewLine;
   std::function<void(const char *, const char *)> addNewCodeLine;
   std::function<void(const char *, const char *)> createObject;
   std::function<void(const char *, const char *)> createExam;
   std::function<void(const char *, const char *)> createExams;
   std::function<void(const char *, const char *)> createItem;
   std::function<void(const char *, const char *)> createHeader;
   std::function<void(const char *, const char *)> createOption;
   std::function<void(const char *, const char *)> setOptionCorrect;
   std::function<void(const char *, const char *)> createGen;
   std::function<void(const char)> resetItemScope;
   std::function<void(const char *, const char *)> assignment;
   std::function<void(std::string &)> retrieve;
   std::function<void(const char *, const char *)> addTextToGen;
   std::function<void(const char *, const char *)> addTextToStem;
   std::function<void(const char *, const char *)> setLevelOfItem;
   std::function<void(const char *, const char *)> addGenToGen;
   std::function<void(const char *, const char *)> addFunctorResultToGen;
   std::function<void(const char *, const char *)> endOfSpec;
   std::function<void(const char *, const char *)> localFunctionCall;
   std::function<void(const char *, const char *)> memberFunctionCall;
   std::function<void(const char *, const char *)> functionCall;

   ExamBuilder(std::vector<Reader::message_t> &messages)
      : error_{ERROR::NO}
      , messages_{messages}
      , isArrayElement_{false}

      , errorMessage(std::bind(&ExamBuilder::do_errorMessage, this,
                               std::placeholders::_1, std::placeholders::_2))

      , initText(std::bind(&ExamBuilder::do_initText, this,
                           std::placeholders::_1, std::placeholders::_2))

      , addChar(
           std::bind(&ExamBuilder::do_addChar, this, std::placeholders::_1))

      , concatText(std::bind(&ExamBuilder::do_concatText, this,
                             std::placeholders::_1, std::placeholders::_2))

      , addNewLine(std::bind(&ExamBuilder::do_addNewLine, this,
                             std::placeholders::_1, std::placeholders::_2))

      , addNewCodeLine(std::bind(&ExamBuilder::do_addNewCodeLine, this,
                                 std::placeholders::_1, std::placeholders::_2))

      , createObject(std::bind(&ExamBuilder::do_createObject, this,
                               std::placeholders::_1, std::placeholders::_2))

      , createExam(std::bind(&ExamBuilder::do_createExam, this,
                             std::placeholders::_1, std::placeholders::_2))

      , createExams(std::bind(&ExamBuilder::do_createExams, this,
                              std::placeholders::_1, std::placeholders::_2))

      , createItem(std::bind(&ExamBuilder::do_createItem, this,
                             std::placeholders::_1, std::placeholders::_2))

      , createHeader(std::bind(&ExamBuilder::do_createHeader, this,
                               std::placeholders::_1, std::placeholders::_2))

      , createOption(std::bind(&ExamBuilder::do_createOption, this,
                               std::placeholders::_1, std::placeholders::_2))

      , setOptionCorrect(std::bind(&ExamBuilder::do_setOptionCorrect, this,
                                   std::placeholders::_1,
                                   std::placeholders::_2))

      , createGen(std::bind(&ExamBuilder::do_createGen, this,
                            std::placeholders::_1, std::placeholders::_2))

      , resetItemScope(std::bind(&ExamBuilder::do_resetItemScope, this,
                                 std::placeholders::_1))

      , assignment(std::bind(&ExamBuilder::do_assignment, this,
                             std::placeholders::_1, std::placeholders::_2))

      , retrieve(
           std::bind(&ExamBuilder::do_retrieve, this, std::placeholders::_1))

      , addTextToGen(std::bind(&ExamBuilder::do_addTextToGen, this,
                               std::placeholders::_1, std::placeholders::_2))

      , addTextToStem(std::bind(&ExamBuilder::do_addTextToStem, this,
                                std::placeholders::_1, std::placeholders::_2))

      , setLevelOfItem(std::bind(&ExamBuilder::do_setLevelOfItem, this,
                                 std::placeholders::_1, std::placeholders::_2))

      , addGenToGen(std::bind(&ExamBuilder::do_addGenToGen, this,
                              std::placeholders::_1, std::placeholders::_2))

      , addFunctorResultToGen(std::bind(&ExamBuilder::do_addFunctorResultToGen,
                                        this, std::placeholders::_1,
                                        std::placeholders::_2))

      , endOfSpec(std::bind(&ExamBuilder::do_endOfSpec, this,
                            std::placeholders::_1, std::placeholders::_2))

      , localFunctionCall(std::bind(&ExamBuilder::do_localFunctionCall, this,
                                    std::placeholders::_1,
                                    std::placeholders::_2))

      , memberFunctionCall(std::bind(&ExamBuilder::do_memberFunctionCall, this,
                                     std::placeholders::_1,
                                     std::placeholders::_2))

      , functionCall(std::bind(&ExamBuilder::do_functionCall, this,
                               std::placeholders::_1, std::placeholders::_2))
   {
      vars_p.add("AppName", APPNAME);
      vars_p.add("Version", VERSION);

      LOGI("initialised");
   }

   // Helper functions
   bool idGeneratorIsUnique(const std::string &id, const char *begin,
                            const char *end);
   IGenPtr_t *idGeneratorIsAvailable(const std::string &id, const char *begin,
                                     const char *end);
   // Error function
   void do_errorMessage(const char *begin, const char *end);

   void do_initText(const char *begin, const char *end)
   {
      // removes leading and trailing "
      LOGCE((*begin) != '"', "No leading \"");
      LOGCE((*(end - 1)) != '"', "No trailing \"");
      text = std::string(begin + 1, end - 1);
   }

   void do_addChar(const char begin) { text += begin; }

   void do_concatText(const char *begin, const char *end)
   {
      text += std::string(begin + 1, end - 1);
   }

   void do_addNewLine(const char * /* begin */, const char * /* end */)
   {
      // Force replacing of " by a space.
      // bug parser?
      *(text.end() - 1) = ' ';
      text += "\n";

      LOGD(text, 3);
   }

   void do_addNewCodeLine(const char * /* begin */, const char * /* end */)
   {
      // Force replacing of " by a space.
      // bug parser?
      *(text.end() - 1) = ' ';
      text += "\n";
      // text.replace( = ' ';
      //*(text.end()-1) = ' ';

      // auto context = util::removeNewLines(util::limitSize(text, 60));
      // LOGD(context, 3);
   }

   void do_assignment(const char *begin, const char * /* end */)
   {
      auto context = util::removeNewLines(util::limitSize(begin, 60));
      LOGD(context, 3);

      if (!itemScope.empty()) {
         lhs = itemScope + "." + lhs;
      }
      auto p = bsc::find(vars_p, lhs.c_str());
      if (p) {
         LOGE("'" + id_ + "', constant '" + lhs + "' already exists!");
         messages_.push_back(Reader::message_t(
            'E', 0, begin, "Constant '" + lhs + "' already exists!"));
      } else {
         bsc::add(vars_p, lhs.c_str(), rhs);
      }
   }

   void do_retrieve(std::string &s)
   {
      auto context = util::removeNewLines(util::limitSize(s, 60));
      LOGD(context, 3);

      rhs.append(" ").append(s);
   }

   void do_createExam(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGI(id_);

      if (not itemScope.empty()) {
         LOGE(id_ + ", Exam '" + id_ + "' should be declared global!");
         messages_.push_back(Reader::message_t(
            'E', 0, begin, "Exam '" + id_ + "' should be declared global!"));
      } else {
         if (idGeneratorIsUnique(id_, begin, end)) {
            std::shared_ptr<GenExams> pExams(new GenExams(id_, messages_, 1));
            bsc::add(generators_p, id_.c_str(),
                     std::static_pointer_cast<IGenerator>(pExams));
            examScope = id_;
            Product.push_back(pExams);
         }
      }
   }

   void do_createExams(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGI("'" + id_ + "' type = " + type);

      std::vector<std::shared_ptr<GenExams>> &ProductLocal(Product);

      if (not itemScope.empty()) {
         messages_.push_back(Reader::message_t(
            'E', 0, begin,
            "Exam array '" + id_ + "' should be declared global!"));
      } else {
         if (idGeneratorIsUnique(id_, begin, end)) {
            std::shared_ptr<GenExams> pExams(
               new GenExams(id_, messages_, par_));
            bsc::add(generators_p, id_.c_str(),
                     std::static_pointer_cast<IGenerator>(pExams));
            Product.push_back(pExams);
         }
      }
   }

   void do_createItem(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGI("'" + id_ + "'");

      if (idGeneratorIsUnique(id_, begin, end)) {
         p_actualItem = std::shared_ptr<GenItem>(new GenItem(id_));
         bsc::add(generators_p, id_.c_str(),
                  std::static_pointer_cast<IGenerator>(p_actualItem));
         itemScope = id_;
         LOGD("set itemScope = " + itemScope, 3);
         bsc::add(generators_p, (id_ + std::string(".level")).c_str(),
                  static_cast<IGenPtr_t>((*p_actualItem)[0]));
         bsc::add(generators_p, (id_ + std::string(".stem")).c_str(),
                  static_cast<IGenPtr_t>((*p_actualItem)[0]));
         // genFactory.addGenerator(id_, p_actualItem);
      }
   }

   void do_createObject(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGI(id_ + " type = " + type);

      if (idGeneratorIsUnique(id_, begin, end)) {
         if (type == "Selector") {
            std::shared_ptr<GenSelector> pS(new GenSelector(id_));
            bsc::add(generators_p, id_.c_str(),
                     std::static_pointer_cast<IGenerator>(pS));
         } else {
            if (type == "LogicDiagramAON") {
               std::shared_ptr<GenLogicDiagramAON> pLD(new GenLogicDiagramAON);
               pLD->setID(id_);
               bsc::add(generators_p, id_.c_str(),
                        std::static_pointer_cast<IGenerator>(pLD));
            } else {
               if (type == "LogicExprAON") {
                  std::shared_ptr<GenLogicExprAON> pLE(
                     new GenLogicExprAON(id_));
                  bsc::add(generators_p, id_.c_str(),
                           std::static_pointer_cast<IGenerator>(pLE));
               } else {
                  if (type == "LogicDiagramAOXN") {
                     std::shared_ptr<GenLogicDiagramAOXN> pL(
                        new GenLogicDiagramAOXN);
                     pL->setID(id_);
                     bsc::add(generators_p, id_.c_str(),
                              std::static_pointer_cast<IGenerator>(pL));
                  } else {
                     if (type == "LogicExprAOXN") {
                        std::shared_ptr<GenLogicExprAOXN> pLE(
                           new GenLogicExprAOXN);
                        pLE->setID(id_);
                        bsc::add(generators_p, id_.c_str(),
                                 std::static_pointer_cast<IGenerator>(pLE));
                     } else {
                        if (type == "TwoC") {
                           std::shared_ptr<GenTwoC> pTC(new GenTwoC);
                           pTC->setID(id_);
                           bsc::add(generators_p, id_.c_str(),
                                    std::static_pointer_cast<IGenerator>(pTC));
                        } else {
                           if (type == "NestedFor") {
                              std::shared_ptr<GenNestedFor> pNF(
                                 new GenNestedFor(id_));
                              bsc::add(
                                 generators_p, id_.c_str(),
                                 std::static_pointer_cast<IGenerator>(pNF));
                           } else {
                              LOGE(id_ + ", type '" + type + "' unknown");
                              messages_.push_back(Reader::message_t(
                                 'E', 0, begin, "Type '" + type + "' unknown"));
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   void do_createHeader(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      if (idGeneratorIsUnique(id_, begin, end)) {
         p_actualHeader = std::shared_ptr<GenHeader>(new GenHeader(id_));
         p_actualHeader->setID(id_);
         p_actualHeader->School = tempHeader.School;
         p_actualHeader->Course = tempHeader.Course;
         p_actualHeader->Lecturer = tempHeader.Lecturer;
         p_actualHeader->Other = tempHeader.Other;
         p_actualHeader->BoxedText = tempHeader.BoxedText;

         bsc::add(generators_p, id_.c_str(),
                  std::static_pointer_cast<IGenerator>(p_actualHeader));
      }
   }

   void do_createOption(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      addItemScope(lhs);
      if (idGeneratorIsUnique(lhs, begin, end)) {
         p_actualOption = std::shared_ptr<GenOption>(new GenOption(lhs, text));
         bsc::add(generators_p, lhs.c_str(),
                  std::static_pointer_cast<IGenerator>(p_actualOption));
         // Add option to related item
         if (auto ppIGen = idGeneratorIsAvailable(itemScope, begin, end)) {
            if (std::shared_ptr<GenItem> pItem =
                   std::dynamic_pointer_cast<GenItem>(*ppIGen)) {
               pItem->addToOptions(p_actualOption);
            }
         }
      }
   }

   void do_setOptionCorrect(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));

      try {
         addItemScope(lhs);
         // Set option to be correct
         if (auto ppIGen = idGeneratorIsAvailable(lhs, begin, end)) {
            if (GenOption *pOption =
                   dynamic_cast<GenOption *>((*ppIGen).get())) {
               pOption->setIsCorrect();
               LOGI("'" + pOption->getID() + "' is correct");
            } else {
               LOGE("'" + id_ + "', option '" + lhs +
                    "' could not set to be correct");
               messages_.push_back(Reader::message_t(
                  'E', 0, begin,
                  "Option '" + lhs + "' could not set to be correct"));
            }
         }
      }
      catch (std::runtime_error &X) {
         std::cerr << X.what() << std::endl;
         LOGE(X.what());
      }
   }

   void do_createGen(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      addItemScope(id_);
      if (idGeneratorIsUnique(id_, begin, end)) {
         if (type == "Header") {
            auto pHeader = std::make_shared<GenHeader>(id_);
            bsc::add(generators_p, id_.c_str(),
                     std::static_pointer_cast<IGenerator>(pHeader));
            p_actualHeader = pHeader;
         } else {
            if (type == "CodeText") {
               auto pCodeText = std::make_shared<GenCodeText>(id_, "C", text);
               bsc::add(generators_p, id_.c_str(),
                        std::static_pointer_cast<IGenerator>(pCodeText));
            } else {
               if (type == "Image") {
                  auto pImage = std::make_shared<GenImage>(id_, text);
                  bsc::add(generators_p, id_.c_str(),
                           std::static_pointer_cast<IGenerator>(pImage));
               } else {
                  if (type == "APIdoc") {
                     if (parList.size() == 3) {
                        auto pAPI = std::make_shared<GenAPI>(
                           parList[0], parList[1], parList[2]);
                        pAPI->setID(id_);
                        bsc::add(generators_p, id_.c_str(),
                                 std::static_pointer_cast<IGenerator>(pAPI));
                     } else {
                        LOGE(id_ + ", API '" + rhs +
                             "' must have 3 parameters!");
                        messages_.push_back(Reader::message_t(
                           'E', 0, begin,
                           "API '" + rhs + "' must have 3 parameters!"));
                     }
                     parList.clear();
                  }
               }
            }
         }
      }
   }

   void do_resetItemScope(const char) { itemScope = ""; }

   void do_addTextToGen(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         std::shared_ptr<GenText> pT(new GenText(lhs + ".txt", text));
         (*ppGenLHS)->add(pT);
      }
   }

   void do_addTextToStem(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         std::shared_ptr<GenText> pT(new GenText(lhs + ".txt", text.c_str()));
         (*ppGenLHS)->add(pT);
      }
   }

   void do_setLevelOfItem(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         (*ppGenLHS)->setLevel(level_);
      }
   }

   /// Example: Exam mct; Item I1 {...}; mct += I1;
   /// Always add a copy of RHS object, except for a Selector, copy contained
   /// Item's.
   void do_addGenToGen(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));

      addItemScope(lhs);
      addItemScope(rhs);

      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         LOGD(lhs + " is available (lhs)", 3);
         if (auto ppGenRHS = idGeneratorIsAvailable(rhs, begin, end)) {
            LOGD(rhs + " is available (rhs)", 3);
            if (isArrayElement_) {
               isArrayElement_ = false;
               if ((*ppGenLHS)->getType() == "GenExams[]") {
                  auto pGenExams = static_cast<GenExams *>((*ppGenLHS).get());
                  if (par_ > (pGenExams->size() - 1)) {
                     LOGE(id_ + ",  array index of '" + lhs +
                          "' exceeds array size.");
                     messages_.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Array index of '" + lhs + "' exceeds array size."));
                  } else {
                     if ((*ppGenRHS)->getType() == "GenSelector") {
                        auto pGenSelector =
                           static_cast<GenSelector *>((*ppGenRHS).get());
                        pGenSelector->selectR(1);
                        (*pGenExams)[par_]->add(*ppGenRHS);
                     } else {
                        /// @todo Remove prepare(), only used by #GenTwoC
                        LOGD("Parser: copy() used, for " + (*ppGenRHS)->getID(),
                             3);
                        (*ppGenRHS)->prepare();
                        auto pGenRHScopy = (*ppGenRHS)->copy();
                        (*pGenExams)[par_]->add(pGenRHScopy);
                     }
                  }
               } else {
                  LOGE(id_ + ", " + lhs + "' is not an array type!");
                  messages_.push_back(Reader::message_t(
                     'E', 0, begin, "'" + lhs + "' is not an array type!"));
               }
            } else {
               if ((*ppGenRHS)->getType() == "GenSelector") {
                  auto pGenSelector =
                     static_cast<GenSelector *>((*ppGenRHS).get());
                  pGenSelector->selectR(1);
                  (*ppGenLHS)->add(*ppGenRHS);
               } else {
                  /// @todo Remove prepare(), only used by #GenTwoC
                  (*ppGenRHS)->prepare();
                  LOGD("Parser: copy() used, for " + (*ppGenRHS)->getID(), 3);
                  auto pGenRHScopy = (*ppGenRHS)->copy();
                  (*ppGenLHS)->add(pGenRHScopy);
               }
            }
         }
      }
   }

   /// Example: Exam mct; Selector S; ... mct += S(3);
   void do_addFunctorResultToGen(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGI(id_ + " type = " + type);

      addItemScope(lhs);
      addItemScope(rhs);

      parList.erase(std::remove(parList.begin(), parList.end(), ""),
                    parList.end());
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         if (auto ppGenRHS = idGeneratorIsAvailable(rhs, begin, end)) {
            if ((*ppGenRHS)->getType() == "GenSelector") {
               if (parList.size() != 1) {
                  LOGE(id_ + ", functor '" + rhs + "' must have 1 parameter!");
                  messages_.push_back(Reader::message_t(
                     'E', 0, begin,
                     "Functor '" + rhs + "' must have 1 parameter!"));
               } else {
                  auto pGenSelector =
                     static_cast<GenSelector *>((*ppGenRHS).get());
                  auto par1 = atoi(parList[0].c_str());
                  if (par1 > pGenSelector->sizeAll()) {
                     par1 = pGenSelector->sizeAll();
                     LOGW(id_ + ", functor '" + rhs +
                          "' parameter value limited to size of Selector");
                     messages_.push_back(Reader::message_t(
                        'W', 0, begin,
                        "Functor '" + rhs +
                           "' parameter value limited to size of Selector"));
                  }
                  if (par1 <= 0) {
                     par1 = 0;
                     LOGE(id_ + ", functor '" + rhs +
                          "'' must have parameter value > 0 !");
                     messages_.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Functor '" + rhs +
                           "' must have parameter value > 0 !"));
                  }
                  if ((*ppGenLHS)->getType() == "GenExams[]") {
                     auto pGenExams =
                        static_cast<GenExams *>((*ppGenLHS).get());
                     auto const nExams = pGenExams->size();
                     for (size_t i = 0; i < nExams; ++i) {
                        pGenSelector->selectR(par1);
                        pGenExams->getGenerators()[i]->add(*ppGenRHS);
                     }
                  } else {
                     pGenSelector->selectR(par1);
                     (*ppGenLHS)->add(*ppGenRHS);
                  }
               }
            } else {
               LOGE(id_ + ", functor for '" + rhs + "' not available");
               messages_.push_back(Reader::message_t(
                  'E', 0, begin, "Functor for '" + rhs + "' not available."));
            }
         }
      }
      parList.clear();
   }

   void do_endOfSpec(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);
   }

   void do_localFunctionCall(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      try {
         /// @bug Workaround: remove empty strings from parList
         parList.erase(std::remove(parList.begin(), parList.end(), ""),
                       parList.end());

         if (function_id == "shuffleON") {
            if (parList.size() != 0) {
               LOGE(id_ + ", function '" + function_id +
                    "' must have 0 parameters!");
               messages_.push_back(Reader::message_t(
                  'E', 0, begin,
                  "Function '" + function_id + "' must have 0 parameters!"));
            } else {
               p_actualItem->shuffleON();
               parList.clear();
            }
         } else {
            parList.clear();
            LOGE(id_ + ", function '" + std::string(begin, end) +
                 "' does not exists!");
            messages_.push_back(Reader::message_t(
               'E', 0, begin,
               "Function '" + std::string(begin, end) + "' does not exists!"));
         }
      }
      catch (std::runtime_error &X) {
         std::cerr << X.what() << std::endl;
         LOGE(X.what());
      }
   }

   void do_memberFunctionCall(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      try {
         /// @bug Workaround: remove empty strings from parList
         parList.erase(std::remove(parList.begin(), parList.end(), ""),
                       parList.end());

         if (auto ppIGen = idGeneratorIsAvailable(lhs, begin, end)) {
            if (std::shared_ptr<GenItem> pItem =
                   std::dynamic_pointer_cast<GenItem>(*ppIGen)) {
               if (function_id == "shuffle") {
                  // pItem->shuffleOptions();
                  parList.clear();
               } else {
                  if (function_id == "sort") {
                     pItem->sortOptions();
                     parList.clear();
                  } else {
                     parList.clear();
                     LOGE(id_ + ", function '" + std::string(begin, end) +
                          "' does not exists!");
                     messages_.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Function '" + std::string(begin, end) +
                           "' does not exists!"));
                  }
               }
            } else {
               if (std::shared_ptr<GenSelector> pSelector =
                      std::dynamic_pointer_cast<GenSelector>(*ppIGen)) {
                  /// @todo Parameter type checking
                  if (function_id == "selectR") {
                     if (parList.size() != 1) {
                        LOGE(id_ + ", number of parameters '" +
                             std::string(begin, end) + "' should be 1");
                        messages_.push_back(Reader::message_t(
                           'E', 0, begin,
                           "Number of parameters '" + std::string(begin, end) +
                              "' should be 1"));
                     }
                     int par1 = atoi(parList[0].c_str());
                     pSelector->selectR(par1);
                     parList.clear();
                  } else {
                     parList.clear();
                     LOGE(id_ + ", function '" + std::string(begin, end) +
                          "' does not exists!");
                     messages_.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Function '" + std::string(begin, end) +
                           "' does not exists!"));
                  }
               }
            }
         } else {
            LOGE(id_ + ", function '" + lhs + "' does not exists!");
            messages_.push_back(Reader::message_t(
               'E', 0, begin, "'" + lhs + "' does not exists!"));
         }
      }
      catch (std::runtime_error &X) {
         std::cerr << X.what() << std::endl;
         LOGE(X.what());
      }
   }

   void do_functionCall(const char *begin, const char *end)
   {
      auto context = util::removeNewLines(util::limitSize(begin, end, 60));
      LOGD(context, 3);

      try {
         /// @bug Workaround: remove empty strings from parList
         parList.erase(std::remove(parList.begin(), parList.end(), ""),
                       parList.end());

         if (type == "Item") {
            if (auto ppIGenLHS = idGeneratorIsUnique(id_, begin, end)) {
               // IGenPtr_t *ppGenLHS2(0);
               std::vector<IGenPtr_t> pGens;
               for (size_t i = 0; i < parList.size(); ++i) {
                  if (auto ppGenLHS2 =
                         idGeneratorIsAvailable(parList[i], begin, end)) {
                     pGens.push_back(*ppGenLHS2);
                  }
               }
               if (parList.size() > 0) {
                  int r = randomProfile.generate(
                     RandomProfile::range_t(0, parList.size() - 1));
                  std::cout << "--- Info r:"
                            << " " << r << std::endl;
                  bsc::add(generators_p, id_.c_str(),
                           std::static_pointer_cast<IGenerator>(pGens.at(r)));
               }
            }
         }
         parList.clear();
      }
      catch (std::runtime_error &X) {
         std::cerr << X.what() << std::endl;
      }
   }

   void addItemScope(std::string &id)
   {
      if (!itemScope.empty()) {
         id = itemScope + "." + id;
         LOGD("itemScope = " + itemScope + "  id = '" + id + "'", 3);
      } else {
         LOGD("id = '" + id + "'", 3);
      }
   }

   std::vector<std::shared_ptr<GenExams>> getProduct()
   {
      LOGI("size = " + std::to_string(Product.size()));

      return Product;
   }
};

// void print(const char *begin, const char *end);
void linecount(const char *, const char *);

struct skipparser : public bsc::grammar<skipparser> {
   template <typename ScannerT> struct definition {
      bsc::rule<ScannerT> skip;

      definition(skipparser const &self)
      {
         skip = bsc::comment_p("//") | bsc::eol_p[&linecount] | bsc::blank_p;
      }

      const bsc::rule<ScannerT> &start() { return skip; }
   };
};

struct ExamSpecParser : public bsc::grammar<ExamSpecParser> {
   ExamBuilder &examBuilder_;

   ExamSpecParser(ExamBuilder &examBuilder)
      : examBuilder_{examBuilder}
   {
      LOGD("initialised", 2);
   }

   template <typename ScannerT> struct definition {
      definition(ExamSpecParser const &self)
      {
         ExamBuilder &pb = self.examBuilder_;

         keywords = "Item", "Header", "Text", "API", "Selector", "stem",
         "level";

         bsc::strlit<> ASSIGN("=");
         bsc::strlit<> LPAREN("(");
         bsc::strlit<> RPAREN(")");
         bsc::strlit<> SEMI(";");

         std::string TEST;

         // Exam or Exam[n]
         // 1 or n Headers
         //    Header: SchoolName + CourseName + LecturerName + Date +
         //    BoxedText
         // m Items
         //    Item: Stem + 3..5 Options
         //       Stem: Text + CodeText + APIdoc
         //       Option: Text + CodeText + APIdoc
         // Selector

         main =
            (Exam |
             Error[bsc::assign_a(pb.error_, ExamBuilder::ERROR::EXM_EXPECTED)]
                  [pb.errorMessage]) >>
            *(Header | Item | Declaration | CodeText | Image | APIdoc | Add |
              AddText | memberFunctionCall) >>
            bsc::end_p[pb.endOfSpec];

         Type =
            (bsc::strlit<>("Selector") | bsc::strlit<>("LogicDiagramAON") |
             bsc::strlit<>("LogicExprAON") | bsc::strlit<>("LogicDiagramAOXN") |
             bsc::strlit<>("LogicExprAOXN") | bsc::strlit<>("TwoC") |
             bsc::strlit<>("NestedFor"))[bsc::assign_a(pb.type)];

         Declaration =
            (Type >> id[bsc::assign_a(pb.id_)] >> SEMI)[pb.createObject];

         Exam = (bsc::strlit<>("Exam")[bsc::assign_a(pb.type)] >>
                 id[bsc::assign_a(pb.id_)] >> SEMI[pb.createExam]) |
                (bsc::strlit<>("Exam")[bsc::assign_a(pb.type)] >>
                 id[bsc::assign_a(pb.id_)] >> bsc::ch_p('[') >>
                 (bsc::int_p[bsc::assign_a(pb.par_)] |
                  Error[bsc::assign_a(pb.error_,
                                      ExamBuilder::ERROR::UNSIGNEDINT_EXPECTED)]
                       [pb.errorMessage]) >>
                 (bsc::ch_p(']') |
                  Error[bsc::assign_a(
                     pb.error_, ExamBuilder::ERROR::CLOSING_BRACKET_EXPECTED)]
                       [pb.errorMessage]) >>
                 (SEMI[pb.createExams] |
                  Error[bsc::assign_a(pb.error_,
                                      ExamBuilder::ERROR::SEMICOLON_EXPECTED)]
                       [pb.errorMessage]));

         Header = bsc::strlit<>("Header")[bsc::assign_a(pb.type)] >>
                  id[bsc::assign_a(pb.id_)] >>
                  // bsc::ch_p('(') >> arglist >> bsc::ch_p(')') >> eol_p >>
                  HeaderBlock[pb.createHeader] >> SEMIexpected;

         HeaderBlock =
            bsc::strlit<>("{") >> bsc::strlit<>("school") >> assignment_op >>
            textLines[bsc::assign_a(pb.tempHeader.School, pb.text)] >> SEMI >>
            bsc::strlit<>("course") >> assignment_op >>
            textLines[bsc::assign_a(pb.tempHeader.Course, pb.text)] >> SEMI >>
            bsc::strlit<>("lecturer") >> assignment_op >>
            textLines[bsc::assign_a(pb.tempHeader.Lecturer, pb.text)] >> SEMI >>
            bsc::strlit<>("date") >> assignment_op >>
            textLines[bsc::assign_a(pb.tempHeader.Other, pb.text)] >> SEMI >>
            bsc::strlit<>("boxedtext") >> assignment_op >>
            textLines[bsc::assign_a(pb.tempHeader.BoxedText, pb.text)] >>
            SEMI >> bsc::strlit<>("}");

         Item = bsc::strlit<>("Item")[bsc::assign_a(pb.type)] >>
                id[bsc::assign_a(pb.id_)][bsc::assign_a(pb.rhs)] >>
                // bsc::ch_p('(') >> arglist >> bsc::ch_p(')')
                (ItemBlock | itemAssignment[pb.functionCall]) >> SEMIexpected;

         ItemBlock = bsc::strlit<>("{")[pb.createItem] >> !levelAssignment >>
                     stemAssignment >> *(CodeText | APIdoc | optionAssignment |
                                         AddGenerator | AddText) >>
                     *localFunctionCall >> bsc::ch_p('}')[pb.resetItemScope];

         levelAssignment =
            (bsc::strlit<>("level")[bsc::assign_a(pb.lhs)] >> assignment_op >>
             bsc::int_p[bsc::assign_a(pb.level_)] >>
             SEMIexpected[pb.setLevelOfItem]);

         stemAssignment =
            (bsc::strlit<>("stem")[bsc::assign_a(pb.lhs)] >> assignment_op >>
             textLines >> SEMIexpected[pb.addTextToStem]);

         Text = bsc::strlit<>("Text")[bsc::assign_a(pb.type)] >>
                (id[bsc::assign_a(pb.lhs)] >> assignment_op >>
                 +(textLine[bsc::assign_a(pb.rhs)] |
                   pb.vars_p[pb.retrieve]))[pb.assignment];

         CodeText = (bsc::strlit<>("CodeText")[bsc::assign_a(pb.type)] >>
                     id[bsc::assign_a(pb.lhs)][bsc::assign_a(pb.id_)] >>
                     assignment_op[bsc::assign_a(pb.text, "")] >> codeLines >>
                     SEMI)[pb.assignment][pb.createGen];

         APIdoc = (bsc::strlit<>("APIdoc")[bsc::assign_a(pb.type)] >>
                   id[bsc::assign_a(pb.lhs)][bsc::assign_a(pb.id_)] >> LPAREN >>
                   textLine[bsc::push_back_a(pb.parList)] >> bsc::ch_p(',') >>
                   textLine[bsc::push_back_a(pb.parList)] >> bsc::ch_p(',') >>
                   textLine[bsc::push_back_a(pb.parList)] >> RPAREN >>
                   SEMI)[pb.assignment][pb.createGen];

         Image =
            (bsc::strlit<>("Image")[bsc::assign_a(pb.type)] >>
             id[bsc::assign_a(pb.lhs)][bsc::assign_a(pb.id_)] >>
             assignment_op >> codeLines >> SEMI)[pb.assignment][pb.createGen];

         optionAssignment = optionId[bsc::assign_a(pb.lhs)] >> assignment_op >>
                            (textLines[pb.createOption] |
                             bsc::strlit<>("correct")[pb.setOptionCorrect]) >>
                            SEMI;

         /*levelAssignment =
         (bsc::strlit<>("level")[bsc::assign_a(pb.type)] >>
         id[bsc::assign_a(pb.lhs)][bsc::assign_a(pb.id_)] >> assignment_op >>
         >> SEMI)[pb.assignment]
         ;*/

         itemAssignment = assignment_op >> id[bsc::assign_a(pb.rhs)] >>
                          LPAREN >> CSV >> RPAREN >> SEMIexpected;

         // Add =
         //(AddGenerator | AddFunctorResult | AddMemberFunctionResult);

         Add =
            (optionId | id)[bsc::assign_a(pb.lhs)] >>
            bsc::if_p(bsc::ch_p(
               '['))[bsc::int_p[bsc::assign_a(pb.par_)] >>
                     bsc::ch_p(']')[bsc::assign_a(pb.isArrayElement_, true)]] >>
            bsc::strlit<>("+=") >> id[bsc::assign_a(pb.rhs)] >>
            bsc::if_p(LPAREN >> CSV >> RPAREN)[SEMI[pb.addFunctorResultToGen]]
               .else_p[SEMI[pb.addGenToGen]];

         AddGenerator =
            (optionId | id)[bsc::assign_a(pb.lhs)] >> bsc::strlit<>("+=") >>
            id[bsc::assign_a(pb.rhs)][pb.addGenToGen] >> SEMIexpected;

         AddFunctorResult = (optionId | id)[bsc::assign_a(pb.lhs)] >>
                            bsc::strlit<>("+=") >> functorCall >> SEMIexpected;

         AddMemberFunctionResult = (optionId | id)[bsc::assign_a(pb.lhs)] >>
                                   bsc::strlit<>("+=") >> memberFunctionCall >>
                                   SEMIexpected;

         AddText = id[bsc::assign_a(pb.lhs)] >> bsc::strlit<>("+=") >>
                   textLines[pb.addTextToGen] >> SEMIexpected;

         localFunctionCall = (id[bsc::assign_a(pb.function_id)] >> LPAREN >>
                              CSV >> RPAREN >> SEMI)[pb.localFunctionCall];

         functorCall = id[bsc::assign_a(pb.rhs)] >> LPAREN >> CSV >>
                       RPAREN[pb.addFunctorResultToGen];

         memberFunctionCall =
            (id[bsc::assign_a(pb.lhs)] >> bsc::strlit<>(".") >>
             id[bsc::assign_a(pb.function_id)] >> LPAREN >> CSV >>
             RPAREN)[pb.memberFunctionCall];

         CSV = bsc::list_p((*id)[bsc::push_back_a(pb.parList)], ',') |
               bsc::list_p(*(textLine[bsc::push_back_a(pb.parList)]), ',');

         optionIndex = bsc::int_p[bsc::assign_a(pb.actualOptionIndex)];

         arglist = !(id >> *(bsc::ch_p(',') >> id));

         id =
            bsc::lexeme_d[(bsc::alpha_p >> *(bsc::alnum_p | bsc::ch_p('_')))] |
            bsc::int_p;

         optionId = bsc::lexeme_d[bsc::strlit<>("o[") >> optionIndex >>
                                  bsc::strlit<>("]")];

         textLine = bsc::confix_p(
            '"', *(bsc::anychar_p - bsc::ch_p('"') - bsc::eol_p), '"');

         textLines = textLine[pb.initText] >> *(textLine)[pb.concatText];

         codeLine = bsc::confix_p('"', *(bsc::c_escape_ch_p)[pb.addChar], '"');

         codeLines = +codeLine[pb.addNewCodeLine];

         assignment_op = bsc::ch_p('=');

         SEMIexpected =
            (SEMI | Error[bsc::assign_a(pb.error_,
                                        ExamBuilder::ERROR::SEMICOLON_EXPECTED)]
                         [pb.errorMessage]);

         Error = bsc::epsilon_p;
      }

      bsc::symbols<> keywords;

      using rule_t = bsc::rule<ScannerT>;

      rule_t main, Type, Declaration, Exam, Header, HeaderBlock, Item,
         ItemBlock, levelAssignment, stemAssignment, Text, CodeText, APIdoc,
         Image, optionAssignment, itemAssignment, Add, AddGenerator,
         AddFunctorResult, AddMemberFunctionResult, AddText, functorCall,
         localFunctionCall, memberFunctionCall, CSV, optionIndex, arglist, id,
         optionId, textLine, textLines, codeLine, codeLines, assignment_op,
         SEMIexpected, Error;

      bsc::rule<ScannerT> const &start() const { return main; }
   };
};

#endif
