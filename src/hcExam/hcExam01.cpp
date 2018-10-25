#include "hcExam01.h"
#include "GenHeader.h"
#include "GenItem.h"
#include "GenOption.h"
#include "GenText.h"
#include "Log.h"

#include <vector>

void hcExam01(std::ofstream &LaTeXfile)
{
   LOGD("Generating LaTeX started");

   const bool IS_CORRECT{true};

   //    std::vector<message_t> messages;

   //    std::shared_ptr<GenMCTs> pMCtst(new GenMCTs(messages));
   //    pMCtst->setID("Hard coded test1");

   //    std::shared_ptr<GenItem> pI;
   //    std::shared_ptr<GenText> pT1;
   //    std::shared_ptr<GenText> pT2;
   //    std::shared_ptr<GenText> pT3;
   //    std::shared_ptr<GenJava> pJ1;
   //    std::shared_ptr<GenJava> pJ2;
   //    std::shared_ptr<GenOption> pO1;
   //    std::shared_ptr<GenOption> pO2;
   //    std::shared_ptr<GenOption> pO3;
   //    std::shared_ptr<GenOption> pO4;
   //    std::shared_ptr<GenImage> pImg;

   auto pHeader = std::make_shared<GenHeader>();
   pHeader->setID("h1");
   pHeader->School = "HAN Engineering";
   pHeader->Course = "Introduction C programming";
   pHeader->Lecturer = "Jos Onokiewicz";
   pHeader->Other = "22th September 2018";
   pHeader->BoxedText = "Success!";
   // pMCtst->add(pHeader);

   // Item #1 ------------------------------------------------------------------
   auto pItem = std::make_unique<GenItem>();
   pItem->setID("I1");
   auto pText1 = std::make_unique<GenText>(
      "txt1",
      "Welk van de volgende typen gebruik je om aan te geven dat het een "
      "variabele tekst bevat?");
   auto pO1 = std::make_unique<GenOption>("O1", "Character");
   auto pO2 = std::make_unique<GenOption>("O2", "char");
   auto pO3 = std::make_unique<GenOption>("O3", "String");
   auto pO4 = std::make_unique<GenOption>("O4", "String[ ]");

   //    pItem->addToStem(pText1);
   //    pItem->addToOptions(pO1);
   //    pItem->addToOptions(pO2);
   //    pItem->addToOptions(pO3, IS_CORRECT);
   //    pItem->addToOptions(pO4);
   //    pItem->shuffleON();

   //    pMCtst->add(pI);

   //    pMCtst->generate(TexFile);

   LOGD("Generating LaTeX ready");
}
