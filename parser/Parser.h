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
#include "GenNestedFor.h"
#include "GenOption.h"
#include "GenSelector.h"
#include "GenSolution.h"
#include "GenStem.h"
#include "GenText.h"
#include "GenTwoC.h"
#include "GeneratorFactory.h"
#include "Log.h"
#include "Random.h"
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

using namespace boost::spirit::classic;

// Errors to check for during the parse
enum {
   NO_ERROR = 0,
   ERR_MCT_EXPECTED,
   ERR_CLOSING_BRACKET_EXPECTED,
   ERR_UNSIGNEDINT_EXPECTED,
   ERR_SEMICOLON_EXPECTED
};

/// This structure contains all semantic actions of the parser.
struct MCTestBuilder {
   std::vector<Reader::message_t> &messages;
   RandomProfile randomProfile;
   size_t error;
   std::vector<std::shared_ptr<GenExams>> Product;
   int level;
   std::string type;
   std::string text;
   std::string lhs;
   std::string rhs;
   std::string id;
   std::string itemScope;
   std::shared_ptr<GenItem> p_actualItem;
   GenHeader tempHeader;
   std::shared_ptr<GenHeader> p_actualHeader;
   std::string function_id;
   std::vector<std::string> parList;
   int par;
   int actualOptionIndex;
   std::shared_ptr<GenOption> p_actualOption;
   bool isArrayElement;

   symbols<std::string> vars_p;
   symbols<IGenPtr_t> generators_p;

   GeneratorFactory genFactory;

   std::function<void(const char *, const char *)> errorMessage;
   std::function<void(const char *, const char *)> initText;
   std::function<void(const char)> addChar;
   std::function<void(const char *, const char *)> concatText;
   std::function<void(const char *, const char *)> addNewLine;
   std::function<void(const char *, const char *)> addNewCodeLine;
   std::function<void(const char *, const char *)> createObject;
   std::function<void(const char *, const char *)> createMCT;
   std::function<void(const char *, const char *)> createMCTs;
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

   MCTestBuilder *self() { return this; }

   MCTestBuilder(std::vector<Reader::message_t> &messages)
      : messages(messages)
      , error(NO_ERROR)
      , isArrayElement(false)
      , errorMessage(std::bind(&MCTestBuilder::do_errorMessage, self(),
                               std::placeholders::_1, std::placeholders::_2))
      , initText(std::bind(&MCTestBuilder::do_initText, self(),
                           std::placeholders::_1, std::placeholders::_2))
      , addChar(
           std::bind(&MCTestBuilder::do_addChar, self(), std::placeholders::_1))
      , concatText(std::bind(&MCTestBuilder::do_concatText, self(),
                             std::placeholders::_1, std::placeholders::_2))
      , addNewLine(std::bind(&MCTestBuilder::do_addNewLine, self(),
                             std::placeholders::_1, std::placeholders::_2))
      , addNewCodeLine(std::bind(&MCTestBuilder::do_addNewCodeLine, self(),
                                 std::placeholders::_1, std::placeholders::_2))
      , createMCT(std::bind(&MCTestBuilder::do_createMCT, self(),
                            std::placeholders::_1, std::placeholders::_2))
      , createMCTs(std::bind(&MCTestBuilder::do_createMCTs, self(),
                             std::placeholders::_1, std::placeholders::_2))
      , createItem(std::bind(&MCTestBuilder::do_createItem, self(),
                             std::placeholders::_1, std::placeholders::_2))
      , createObject(std::bind(&MCTestBuilder::do_createObject, self(),
                               std::placeholders::_1, std::placeholders::_2))
      , createHeader(std::bind(&MCTestBuilder::do_createHeader, self(),
                               std::placeholders::_1, std::placeholders::_2))
      , createOption(std::bind(&MCTestBuilder::do_createOption, self(),
                               std::placeholders::_1, std::placeholders::_2))
      , setOptionCorrect(std::bind(&MCTestBuilder::do_setOptionCorrect, self(),
                                   std::placeholders::_1,
                                   std::placeholders::_2))
      , createGen(std::bind(&MCTestBuilder::do_createGen, self(),
                            std::placeholders::_1, std::placeholders::_2))
      , resetItemScope(std::bind(&MCTestBuilder::do_resetItemScope, self(),
                                 std::placeholders::_1))
      , assignment(std::bind(&MCTestBuilder::do_assignment, self(),
                             std::placeholders::_1, std::placeholders::_2))
      , retrieve(std::bind(&MCTestBuilder::do_retrieve, self(),
                           std::placeholders::_1))
      , addTextToGen(std::bind(&MCTestBuilder::do_addTextToGen, self(),
                               std::placeholders::_1, std::placeholders::_2))
      , addTextToStem(std::bind(&MCTestBuilder::do_addTextToStem, self(),
                                std::placeholders::_1, std::placeholders::_2))
      , setLevelOfItem(std::bind(&MCTestBuilder::do_setLevelOfItem, self(),
                                 std::placeholders::_1, std::placeholders::_2))
      , addGenToGen(std::bind(&MCTestBuilder::do_addGenToGen, self(),
                              std::placeholders::_1, std::placeholders::_2))
      , addFunctorResultToGen(
           std::bind(&MCTestBuilder::do_addFunctorResultToGen, self(),
                     std::placeholders::_1, std::placeholders::_2))
      , endOfSpec(std::bind(&MCTestBuilder::do_endOfSpec, self(),
                            std::placeholders::_1, std::placeholders::_2))
      , localFunctionCall(std::bind(&MCTestBuilder::do_localFunctionCall,
                                    self(), std::placeholders::_1,
                                    std::placeholders::_2))
      , memberFunctionCall(std::bind(&MCTestBuilder::do_memberFunctionCall,
                                     self(), std::placeholders::_1,
                                     std::placeholders::_2))
      , functionCall(std::bind(&MCTestBuilder::do_functionCall, self(),
                               std::placeholders::_1, std::placeholders::_2))
   {
      vars_p.add("AppName", APPNAME);
      vars_p.add("Version", VERSION);
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
   }

   void do_addNewCodeLine(const char * /* begin */, const char * /* end */)
   {
      // Force replacing of " by a space.
      // bug parser?
      *(text.end() - 1) = ' ';
      text += "\n";
      // text.replace( = ' ';
      //*(text.end()-1) = ' ';
   }

   void do_assignment(const char *begin, const char *)
   {
      if (!itemScope.empty()) {
         lhs = itemScope + "." + lhs;
      }
      auto p = find(vars_p, lhs.c_str());
      if (p) {
         messages.push_back(Reader::message_t(
            'E', 0, begin, "Constant '" + lhs + "' already exists!"));
      } else {
         boost::spirit::classic::add(vars_p, lhs.c_str(), rhs);
      }
   }

   void do_retrieve(std::string &s) { rhs.append(" ").append(s); }

   void do_createMCT(const char *begin, const char *end)
   {
      if (!itemScope.empty()) {
         messages.push_back(Reader::message_t(
            'E', 0, begin, "MCT '" + id + "' should be declared global!"));
      } else {
         if (idGeneratorIsUnique(id, begin, end)) {
            std::shared_ptr<GenExams> pMCTs(new GenExams(messages, 1));
            pMCTs->setID(id);
            boost::spirit::classic::add(
               generators_p, id.c_str(),
               std::static_pointer_cast<IGenerator>(pMCTs));
            Product.push_back(pMCTs);
         }
      }
   }

   void do_createMCTs(const char *begin, const char *end)
   {
      std::vector<std::shared_ptr<GenExams>> &ProductLocal(Product);

      if (!itemScope.empty()) {
         messages.push_back(Reader::message_t(
            'E', 0, begin,
            "MCT array '" + id + "' should be declared global!"));
      } else {
         if (idGeneratorIsUnique(id, begin, end)) {
            std::shared_ptr<GenExams> pMCTs(new GenExams(messages, par));
            pMCTs->setID(id);
            boost::spirit::classic::add(
               generators_p, id.c_str(),
               std::static_pointer_cast<IGenerator>(pMCTs));
            Product.push_back(pMCTs);
         }
      }
   }

   void do_createItem(const char *begin, const char *end)
   {
      if (idGeneratorIsUnique(id, begin, end)) {
         p_actualItem = std::shared_ptr<GenItem>(new GenItem(id));
         boost::spirit::classic::add(
            generators_p, id.c_str(),
            std::static_pointer_cast<IGenerator>(p_actualItem));
         itemScope = id.c_str();
         boost::spirit::classic::add(generators_p,
                                     (id + std::string(".level")).c_str(),
                                     (IGenPtr_t)((*p_actualItem)[0]));
         boost::spirit::classic::add(generators_p,
                                     (id + std::string(".stem")).c_str(),
                                     (IGenPtr_t)((*p_actualItem)[0]));
         genFactory.addGenerator(id, p_actualItem);
      }
   }

   void do_createObject(const char *begin, const char *end)
   {
      if (idGeneratorIsUnique(id, begin, end)) {
         if (type == "Selector") {
            std::shared_ptr<GenSelector> pS(new GenSelector(id));
            boost::spirit::classic::add(
               generators_p, id.c_str(),
               std::static_pointer_cast<IGenerator>(pS));
         } else {
            if (type == "LogicDiagramAON") {
               std::shared_ptr<GenLogicDiagramAON> pL(new GenLogicDiagramAON);
               pL->setID(id);
               boost::spirit::classic::add(
                  generators_p, id.c_str(),
                  std::static_pointer_cast<IGenerator>(pL));
            } else {
               if (type == "LogicDiagramAOXN") {
                  std::shared_ptr<GenLogicDiagramAOXN> pL(
                     new GenLogicDiagramAOXN);
                  pL->setID(id);
                  boost::spirit::classic::add(
                     generators_p, id.c_str(),
                     std::static_pointer_cast<IGenerator>(pL));
               } else {
                  if (type == "TwoC") {
                     std::shared_ptr<GenTwoC> pTC(new GenTwoC);
                     pTC->setID(id);
                     boost::spirit::classic::add(
                        generators_p, id.c_str(),
                        std::static_pointer_cast<IGenerator>(pTC));
                  } else {
                     if (type == "NestedFor") {
                        std::shared_ptr<GenNestedFor> pNF(new GenNestedFor);
                        pNF->setID(id);
                        boost::spirit::classic::add(
                           generators_p, id.c_str(),
                           std::static_pointer_cast<IGenerator>(pNF));
                     } else {
                        messages.push_back(Reader::message_t(
                           'E', 0, begin, "Type '" + type + "' unknown"));
                     }
                  }
               }
            }
         }
      }
   }

   void do_createHeader(const char *begin, const char *end)
   {
      if (idGeneratorIsUnique(id, begin, end)) {
         p_actualHeader = std::shared_ptr<GenHeader>(new GenHeader(id));
         *p_actualHeader = tempHeader;
         p_actualHeader->setID(id);
         boost::spirit::classic::add(
            generators_p, id.c_str(),
            std::static_pointer_cast<IGenerator>(p_actualHeader));
      }
   }

   void do_createOption(const char *begin, const char *end)
   {
      addItemScope(lhs);
      if (idGeneratorIsUnique(lhs, begin, end)) {
         p_actualOption = std::shared_ptr<GenOption>(new GenOption(text));
         p_actualOption->setID(lhs);
         boost::spirit::classic::add(
            generators_p, lhs.c_str(),
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
      try {
         addItemScope(lhs);
         // Set option to be correct
         if (auto ppIGen = idGeneratorIsAvailable(lhs, begin, end)) {
            if (GenOption *pOption =
                   dynamic_cast<GenOption *>((*ppIGen).get())) {
               pOption->setIsCorrect();
            } else {
               messages.push_back(Reader::message_t(
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
      addItemScope(id);
      if (idGeneratorIsUnique(id, begin, end)) {
         if (type == "Header") {
            std::shared_ptr<GenHeader> pH(new GenHeader(id));
            boost::spirit::classic::add(
               generators_p, id.c_str(),
               std::static_pointer_cast<IGenerator>(pH));
            p_actualHeader = pH;
         } else {
            if (type == "Java") {
               std::shared_ptr<GenCodeText> pJ(new GenCodeText("java", text));
               pJ->setID(id);
               boost::spirit::classic::add(
                  generators_p, id.c_str(),
                  std::static_pointer_cast<IGenerator>(pJ));
            } else {
               if (type == "Image") {
                  std::shared_ptr<GenImage> pI(new GenImage(text));
                  pI->setID(id);
                  boost::spirit::classic::add(
                     generators_p, id.c_str(),
                     std::static_pointer_cast<IGenerator>(pI));
               } else {
                  if (type == "APIdoc") {
                     if (parList.size() == 3) {
                        std::shared_ptr<GenAPI> pI(
                           new GenAPI(parList[0], parList[1], parList[2]));
                        pI->setID(id);
                        boost::spirit::classic::add(
                           generators_p, id.c_str(),
                           std::static_pointer_cast<IGenerator>(pI));
                     } else {
                        messages.push_back(Reader::message_t(
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
      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         std::shared_ptr<GenText> pT(new GenText(text));
         (*ppGenLHS)->add(pT);
      }
   }

   void do_addTextToStem(const char *begin, const char *end)
   {
      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         std::shared_ptr<GenText> pT(new GenText(text.c_str()));
         (*ppGenLHS)->add(pT);
      }
   }

   void do_setLevelOfItem(const char *begin, const char *end)
   {
      addItemScope(lhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         (*ppGenLHS)->setLevel(level);
      }
   }

   /// Example: MCT mct; Item I1 {...}; mct += I1;
   /// Always add a copy of RHS object, except for a Selector, copy contained
   /// Item's.
   void do_addGenToGen(const char *begin, const char *end)
   {
      addItemScope(lhs);
      addItemScope(rhs);
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         if (auto ppGenRHS = idGeneratorIsAvailable(rhs, begin, end)) {
            if (isArrayElement) {
               isArrayElement = false;
               if ((*ppGenLHS)->getType() == "Exams[]") {
                  auto pGenMCTs = static_cast<GenExams *>((*ppGenLHS).get());
                  if (par > (pGenMCTs->size() - 1)) {
                     messages.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Array index of '" + lhs + "' exceeds array size."));
                  } else {
                     if ((*ppGenRHS)->getType() == "Selector") {
                        auto pGenSelector =
                           static_cast<GenSelector *>((*ppGenRHS).get());
                        pGenSelector->selectR(1);
                        (*pGenMCTs)[par]->add(*ppGenRHS);
                     } else {
                        /// @todo Remove prepare(), only used by #GenTwoC
                        (*ppGenRHS)->prepare();
                        auto pGenRHScopy = (*ppGenRHS)->copy();
                        (*pGenMCTs)[par]->add(pGenRHScopy);
                     }
                  }
               } else {
                  messages.push_back(Reader::message_t(
                     'E', 0, begin, "'" + lhs + "' is not an array type!"));
               }
            } else {
               if ((*ppGenRHS)->getType() == "Selector") {
                  auto pGenSelector =
                     static_cast<GenSelector *>((*ppGenRHS).get());
                  pGenSelector->selectR(1);
                  (*ppGenLHS)->add(*ppGenRHS);
               } else {
                  /// @todo Remove prepare(), only used by #GenTwoC
                  (*ppGenRHS)->prepare();
                  auto pGenRHScopy = (*ppGenRHS)->copy();
                  (*ppGenLHS)->add(pGenRHScopy);
               }
            }
         }
      }
   }

   /// Example: MCT mct; Selector S; ... mct += S(3);
   void do_addFunctorResultToGen(const char *begin, const char *end)
   {
      addItemScope(lhs);
      addItemScope(rhs);
      parList.erase(std::remove(parList.begin(), parList.end(), ""),
                    parList.end());
      if (auto ppGenLHS = idGeneratorIsAvailable(lhs, begin, end)) {
         if (auto ppGenRHS = idGeneratorIsAvailable(rhs, begin, end)) {
            if ((*ppGenRHS)->getType() == "GenSelector") {
               if (parList.size() != 1) {
                  messages.push_back(Reader::message_t(
                     'E', 0, begin,
                     "Functor '" + rhs + "' must have 1 parameter!"));
               } else {
                  auto pGenSelector =
                     static_cast<GenSelector *>((*ppGenRHS).get());
                  auto par1 = atoi(parList[0].c_str());
                  if (par1 > pGenSelector->sizeAll()) {
                     par1 = pGenSelector->sizeAll();
                     messages.push_back(Reader::message_t(
                        'W', 0, begin,
                        "Functor '" + rhs +
                           "' parameter value limited to size of Selector"));
                  }
                  if (par1 <= 0) {
                     par1 = 0;
                     messages.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Functor '" + rhs +
                           "' must have parameter value > 0 !"));
                  }
                  if ((*ppGenLHS)->getType() == "Exam[]") {
                     auto pGenMCT = static_cast<GenExams *>((*ppGenLHS).get());
                     auto nMCT = pGenMCT->size();
                     for (size_t i = 0; i < nMCT; ++i) {
                        pGenSelector->selectR(par1);
                        pGenMCT->getGenerators()[i]->add(*ppGenRHS);
                     }
                  } else {
                     pGenSelector->selectR(par1);
                     (*ppGenLHS)->add(*ppGenRHS);
                  }
               }
            } else {
               messages.push_back(Reader::message_t(
                  'E', 0, begin, "Functor for '" + rhs + "' not available."));
            }
         }
      }
      parList.clear();
   }

   void do_endOfSpec(const char *, const char *) {}

   void do_localFunctionCall(const char *begin, const char *end)
   {
      try {
         /// @bug Workaround: remove empty strings from parList
         parList.erase(std::remove(parList.begin(), parList.end(), ""),
                       parList.end());

         if (function_id == "shuffleON") {
            if (parList.size() != 0) {
               messages.push_back(Reader::message_t(
                  'E', 0, begin,
                  "Function '" + function_id + "' must have 0 parameters!"));
            } else {
               p_actualItem->shuffleON();
               parList.clear();
            }
         } else {
            parList.clear();
            messages.push_back(Reader::message_t(
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
                     messages.push_back(Reader::message_t(
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
                        messages.push_back(Reader::message_t(
                           'E', 0, begin,
                           "Number of parameters '" + std::string(begin, end) +
                              "' should be 1"));
                     }
                     int par1 = atoi(parList[0].c_str());
                     pSelector->selectR(par1);
                     parList.clear();
                  } else {
                     parList.clear();
                     messages.push_back(Reader::message_t(
                        'E', 0, begin,
                        "Function '" + std::string(begin, end) +
                           "' does not exists!"));
                  }
               }
            }
         } else {
            messages.push_back(Reader::message_t(
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
      try {
         /// @bug Workaround: remove empty strings from parList
         parList.erase(std::remove(parList.begin(), parList.end(), ""),
                       parList.end());

         if (type == "Item") {
            if (auto ppIGenLHS = idGeneratorIsUnique(id, begin, end)) {
               IGenPtr_t *ppGenLHS2(0);
               std::vector<IGenPtr_t> pGens;
               for (size_t i = 0; i < parList.size(); ++i) {
                  if (auto ppGenLHS2 =
                         idGeneratorIsAvailable(parList[i], begin, end)) {
                     pGens.push_back(*ppGenLHS2);
                  }
               }
               if (parList.size() > 0) {
                  int r = randomProfile.generate(
                     Random::range_t(0, parList.size() - 1));
                  std::cout << "--- Info r:"
                            << " " << r << std::endl;
                  boost::spirit::classic::add(
                     generators_p, id.c_str(),
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
      }
   }

   std::vector<std::shared_ptr<GenExams>> getProduct() { return Product; }
};

extern int line;
void print(const char *begin, const char *end);
void linecount(const char *, const char *);

struct skipparser : public grammar<skipparser> {
   template <typename ScannerT> struct definition {
      rule<ScannerT> skip;

      definition(skipparser const &self)
      {
         skip = comment_p("//") | eol_p[&linecount] | blank_p;
      }

      const rule<ScannerT> &start() { return skip; }
   };
};

struct MCTspecParser : public grammar<MCTspecParser> {
   MCTestBuilder &pb_;

   MCTspecParser(MCTestBuilder &pb)
      : pb_(pb)
   {
   }

   template <typename ScannerT> struct definition {
      definition(MCTspecParser const &self)
      {
         MCTestBuilder &pb = self.pb_;

         keywords = "Item", "Header", "Text", "API", "Selector", "stem",
         "level";

         strlit<> ASSIGN("=");
         strlit<> LPAREN("(");
         strlit<> RPAREN(")");
         strlit<> SEMI(";");

         std::string TEST;

         // GenMCT
         // 1 Header
         //    Header: SchoolName + CourseName + LecturerName + Date + BoxedText
         // n Items
         //    Item: Stem + 3..5 Options
         //       Stem: Text + Java + APIdoc
         //       Option: Text + Java + APIdoc
         // Selector

         main =
            (+MCT |
             Error[assign_a(pb.error, ERR_MCT_EXPECTED)][pb.errorMessage]) >>
            *(Header | Item | Declaration | Java | Image | APIdoc | Add |
              AddText | memberFunctionCall) >>
            end_p[pb.endOfSpec];

         Type = (strlit<>("Selector") | strlit<>("LogicDiagramAON") |
                 strlit<>("LogicDiagramAOXN") | strlit<>("TwoC") |
                 strlit<>("NestedFor"))[assign_a(pb.type)];

         Declaration = (Type >> id[assign_a(pb.id)] >> SEMI)[pb.createObject];

         MCT =
            (strlit<>("MCT")[assign_a(pb.type)] >> id[assign_a(pb.id)] >>
             SEMI[pb.createMCT]) |
            (strlit<>("MCT")[assign_a(pb.type)] >> id[assign_a(pb.id)] >>
             ch_p('[') >> (uint_p[assign_a(pb.par)] |
                           Error[assign_a(pb.error, ERR_UNSIGNEDINT_EXPECTED)]
                                [pb.errorMessage]) >>
             (ch_p(']') |
              Error[assign_a(pb.error, ERR_CLOSING_BRACKET_EXPECTED)]
                   [pb.errorMessage]) >>
             (SEMI[pb.createMCTs] |
              Error[assign_a(pb.error, ERR_SEMICOLON_EXPECTED)]
                   [pb.errorMessage]));

         Header = strlit<>("Header")[assign_a(pb.type)] >>
                  id[assign_a(pb.id)] >>
                  // ch_p('(') >> arglist >> ch_p(')') >> eol_p >>
                  HeaderBlock[pb.createHeader] >> SEMIexpected;

         HeaderBlock = strlit<>("{") >> strlit<>("school") >> assignment_op >>
                       textLines[assign_a(pb.tempHeader.School, pb.text)] >>
                       SEMI >> strlit<>("course") >> assignment_op >>
                       textLines[assign_a(pb.tempHeader.Course, pb.text)] >>
                       SEMI >> strlit<>("lecturer") >> assignment_op >>
                       textLines[assign_a(pb.tempHeader.Lecturer, pb.text)] >>
                       SEMI >> strlit<>("date") >> assignment_op >>
                       textLines[assign_a(pb.tempHeader.Date, pb.text)] >>
                       SEMI >> strlit<>("boxedtext") >> assignment_op >>
                       textLines[assign_a(pb.tempHeader.BoxedText, pb.text)] >>
                       SEMI >> strlit<>("}");

         Item = strlit<>("Item")[assign_a(pb.type)] >>
                id[assign_a(pb.id)][assign_a(pb.rhs)] >>
                // ch_p('(') >> arglist >> ch_p(')')
                (ItemBlock | itemAssignment[pb.functionCall]) >> SEMIexpected;

         ItemBlock = strlit<>("{")[pb.createItem] >> !levelAssignment >>
                     stemAssignment >> *(Java | APIdoc | optionAssignment |
                                         AddGenerator | AddText) >>
                     *localFunctionCall >> ch_p('}')[pb.resetItemScope];

         levelAssignment =
            (strlit<>("level")[assign_a(pb.lhs)] >> assignment_op >>
             int_p[assign_a(pb.level)] >> SEMIexpected[pb.setLevelOfItem]);

         stemAssignment =
            (strlit<>("stem")[assign_a(pb.lhs)] >> assignment_op >> textLines >>
             SEMIexpected[pb.addTextToStem]);

         Text = strlit<>("Text")[assign_a(pb.type)] >>
                (id[assign_a(pb.lhs)] >> assignment_op >>
                 +(textLine[assign_a(pb.rhs)] |
                   pb.vars_p[pb.retrieve]))[pb.assignment];

         Java = (strlit<>("Java")[assign_a(pb.type)] >>
                 id[assign_a(pb.lhs)][assign_a(pb.id)] >>
                 assignment_op[assign_a(pb.text, "")] >> codeLines >>
                 SEMI)[pb.assignment][pb.createGen];

         APIdoc = (strlit<>("APIdoc")[assign_a(pb.type)] >>
                   id[assign_a(pb.lhs)][assign_a(pb.id)] >> LPAREN >>
                   textLine[push_back_a(pb.parList)] >> ch_p(',') >>
                   textLine[push_back_a(pb.parList)] >> ch_p(',') >>
                   textLine[push_back_a(pb.parList)] >> RPAREN >>
                   SEMI)[pb.assignment][pb.createGen];

         Image = (strlit<>("Image")[assign_a(pb.type)] >>
                  id[assign_a(pb.lhs)][assign_a(pb.id)] >> assignment_op >>
                  codeLines >> SEMI)[pb.assignment][pb.createGen];

         optionAssignment = optionId[assign_a(pb.lhs)] >> assignment_op >>
                            (textLines[pb.createOption] |
                             strlit<>("correct")[pb.setOptionCorrect]) >>
                            SEMI;

         /*levelAssignment =
         (strlit<>("level")[assign_a(pb.type)] >>
         id[assign_a(pb.lhs)][assign_a(pb.id)] >> assignment_op >> >>
         SEMI)[pb.assignment]
         ;*/

         itemAssignment = assignment_op >> id[assign_a(pb.rhs)] >> LPAREN >>
                          CSV >> RPAREN >> SEMIexpected;

         // Add =
         //(AddGenerator | AddFunctorResult | AddMemberFunctionResult);

         Add = (optionId | id)[assign_a(pb.lhs)] >>
               if_p(ch_p('['))[uint_p[assign_a(pb.par)] >>
                               ch_p(']')[assign_a(pb.isArrayElement, true)]] >>
               strlit<>("+=") >> id[assign_a(pb.rhs)] >>
               if_p(LPAREN >> CSV >> RPAREN)[SEMI[pb.addFunctorResultToGen]]
                  .else_p[SEMI[pb.addGenToGen]];

         AddGenerator = (optionId | id)[assign_a(pb.lhs)] >> strlit<>("+=") >>
                        id[assign_a(pb.rhs)][pb.addGenToGen] >> SEMIexpected;

         AddFunctorResult = (optionId | id)[assign_a(pb.lhs)] >>
                            strlit<>("+=") >> functorCall >> SEMIexpected;

         AddMemberFunctionResult = (optionId | id)[assign_a(pb.lhs)] >>
                                   strlit<>("+=") >> memberFunctionCall >>
                                   SEMIexpected;

         AddText = id[assign_a(pb.lhs)] >> strlit<>("+=") >>
                   textLines[pb.addTextToGen] >> SEMIexpected;

         localFunctionCall = (id[assign_a(pb.function_id)] >> LPAREN >> CSV >>
                              RPAREN >> SEMI)[pb.localFunctionCall];

         functorCall = id[assign_a(pb.rhs)] >> LPAREN >> CSV >>
                       RPAREN[pb.addFunctorResultToGen];

         memberFunctionCall = (id[assign_a(pb.lhs)] >> strlit<>(".") >>
                               id[assign_a(pb.function_id)] >> LPAREN >> CSV >>
                               RPAREN)[pb.memberFunctionCall];

         CSV = list_p((*id)[push_back_a(pb.parList)], ',') |
               list_p(*(textLine[push_back_a(pb.parList)]), ',');

         optionIndex = uint_p[assign_a(pb.actualOptionIndex)];

         arglist = !(id >> *(ch_p(',') >> id));

         id = lexeme_d[(alpha_p >> *(alnum_p | ch_p('_')))] | int_p;

         optionId = lexeme_d[strlit<>("o[") >> optionIndex >> strlit<>("]")];

         textLine = confix_p('"', *(anychar_p - ch_p('"') - eol_p), '"');

         textLines = textLine[pb.initText] >> *(textLine)[pb.concatText];

         codeLine = confix_p('"', *(c_escape_ch_p)[pb.addChar], '"');

         codeLines = +codeLine[pb.addNewCodeLine];

         assignment_op = ch_p('=');

         SEMIexpected =
            (SEMI | Error[assign_a(pb.error, ERR_SEMICOLON_EXPECTED)]
                         [pb.errorMessage]);

         Error = epsilon_p;
      }

      symbols<> keywords;

      typedef rule<ScannerT> rule_t;
      rule_t main, Type, Declaration, MCT, Header, HeaderBlock, Item, ItemBlock,
         levelAssignment, stemAssignment, Text, Java, APIdoc, Image,
         optionAssignment, itemAssignment, Add, AddGenerator, AddFunctorResult,
         AddMemberFunctionResult, AddText, functorCall, localFunctionCall,
         memberFunctionCall, CSV, optionIndex, arglist, id, optionId, textLine,
         textLines, codeLine, codeLines, assignment_op, SEMIexpected, Error;

      rule<ScannerT> const &start() const { return main; }
   };
};

#endif
