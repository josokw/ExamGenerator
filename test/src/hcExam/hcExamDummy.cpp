// Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus fermentum
// nibh nunc, non viverra sapien volutpat sit amet. Maecenas at arcu posuere,
// cursus est eget, blandit tortor. Sed quis viverra massa. Aenean non felis
// finibus, commodo sem ut, accumsan tellus. Nullam vitae ipsum porta, faucibus
// dolor et, porta justo. Donec vehicula erat ut felis fermentum, eu aliquam leo
// rhoncus. Nullam eu odio diam. Quisque non nulla id enim vulputate pharetra in
// vitae arcu. Quisque elementum quam malesuada metus auctor, quis mattis metus
// rutrum. Vestibulum vitae accumsan purus. Nunc molestie ante ut viverra
// tincidunt. Vestibulum id turpis pulvinar, dictum risus eu, laoreet ex.

// Mauris at ligula pulvinar, venenatis tortor a, euismod sapien. Sed a dictum
// leo. Proin suscipit, enim nec lobortis condimentum, est erat pellentesque
// neque, sit amet hendrerit metus sem vel risus. Maecenas metus diam, lobortis
// id pretium at, tincidunt et massa. Pellentesque habitant morbi tristique
// senectus et netus et malesuada fames ac turpis egestas. Duis imperdiet libero
// sit amet ex bibendum finibus. Aliquam erat volutpat. Praesent posuere nunc at
// laoreet aliquet. Nullam eu mi interdum, maximus mi ac, pretium ipsum. Aliquam
// facilisis lorem in vehicula elementum. Quisque lacus sem, facilisis ac
// pulvinar ac, dictum sit amet elit.

// Nullam sit amet congue nulla. Curabitur a elit hendrerit, egestas nisl id,
// scelerisque nisl. Ut felis risus, venenatis sed nibh at, maximus facilisis
// diam. Vestibulum maximus, metus eget mattis pretium, ex lectus pharetra enim,
// at dictum neque lacus ut ipsum. Mauris lacinia augue in enim varius, id
// iaculis velit aliquam. Cras ullamcorper accumsan elit, ut blandit leo
// efficitur sed. In sed convallis risus, et vehicula odio. Quisque vel orci
// neque. Aliquam tristique quis lorem a laoreet.

// Fusce in magna erat. Cras turpis est, posuere id arcu ut, semper lobortis
// dui. Phasellus urna turpis, pharetra eu ipsum sodales, venenatis sodales
// enim. Aenean eu lacus a ante ultrices tempor. Quisque imperdiet nibh eu massa
// pulvinar consectetur. Quisque viverra, risus nec lacinia euismod, libero
// tortor rutrum purus, quis laoreet ante arcu in nisl. Vivamus luctus lacinia
// posuere. Duis pulvinar sodales metus vel convallis. Mauris nulla massa,
// malesuada malesuada risus vitae, dapibus rhoncus nisi. Suspendisse viverra eu
// nisl in mattis. In finibus nisl sed ipsum sodales, ut gravida erat viverra.

// Praesent viverra nisi et purus gravida, malesuada tincidunt libero rutrum.
// Donec eget urna posuere, lobortis leo a, porttitor ex. Nam accumsan purus vel
// mauris finibus, nec sagittis odio suscipit. Mauris lacinia vehicula lobortis.
// Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac
// turpis egestas. Aenean sit amet fermentum nisl, non posuere leo. Etiam
// facilisis ultrices diam, ac luctus leo ultricies a. Pellentesque lorem urna,
// rutrum at purus ac, gravida porttitor velit. Donec molestie et odio in
// fermentum. Aliquam in sapien eu nisl varius pulvinar.

#include "GenAPI.h"
#include "GenCFactory.h"
#include "GenCodeText.h"
#include "GenExam.h"
#include "GenExams.h"
#include "GenHeader.h"
#include "GenItem.h"
#include "GenLogicFactory.h"
#include "GenNull.h"
#include "GenOption.h"
#include "GenSolution.h"
#include "GenText.h"
#include "Log.h"
#include "hcExam01.h"

#include <memory>
#include <vector>

void hcExamDummy(std::ofstream &LaTeXfile)
{
   LOGI("GenFactory init");

   GenLogicFactory genLogicFactory;
   GenCFactory genCFactory;

   LOGI("Generating LaTeX file started");

   const bool IS_CORRECT{true};

   std::vector<message_t> messages;
   std::shared_ptr<GenExam> pExam(new GenExam("TestExam ", messages));

   {
      // Header ----------------------------------------------------------------
      auto pHeader = std::make_shared<GenHeader>();
      pHeader->setID("h1");
      pHeader->School = "School dummy";
      pHeader->Course = "Magic dummy";
      pHeader->Lecturer = "Code Warrier";
      pHeader->Other = "1 January 2020";
      pHeader->BoxedText = "Success!";

      pExam->add(pHeader);

      // Item #1 ---------------------------------------------------------------
      auto pItem = std::make_shared<GenItem>();
      pItem->setID("I1");

      auto pText = std::make_shared<GenText>(
         "txt",
         "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus "
         "fermentum nibh nunc, non viverra sapien volutpat sit amet. Maecenas "
         "at arcu?");
      pText->setID("I1.text");
      pItem->addToStem(pText);

      auto pO1 = std::make_shared<GenOption>("01.1", "Option 1.");
      auto pO2 = std::make_shared<GenOption>("01.2", "Option 2..");
      auto pO3 = std::make_shared<GenOption>("01.3", "Option 3...");
      auto pO4 = std::make_shared<GenOption>("01.4", "Option 4....");

      pItem->addToOptions(pO1);
      pItem->addToOptions(pO2);
      pItem->addToOptions(pO3, IS_CORRECT);
      pItem->addToOptions(pO4);

      pExam->add(pItem);
   }

   std::cerr << "\n" << *pExam << std::endl;

   // Item #2 ------------------------------------------------------------------
   {
      auto pItem = std::make_shared<GenItem>();
      pItem->setID("I2");
      auto pText = std::make_shared<GenText>(
         "txt",
         "Fusce in magna erat. Cras turpis est, posuere id arcu ut, semper "
         "lobortis dui. Phasellus urna turpis, pharetra eu ipsum sodales, "
         "venenatis sodales enim?");
      // pText->setID("I2.text");
      pItem->addToStem(pText);

      auto pO1 = std::make_shared<GenOption>("02.1", "Shuffle Option 1.");
      auto pO2 = std::make_shared<GenOption>("02.2", "Shuffle Option 2..");
      auto pO3 = std::make_shared<GenOption>("02.3", "Shuffle Option 3...");
      auto pO4 = std::make_shared<GenOption>("02.4", "Shuffle Option 4....");

      pItem->addToOptions(pO1);
      pItem->addToOptions(pO2, IS_CORRECT);
      pItem->addToOptions(pO3);
      pItem->addToOptions(pO4);
      pItem->shuffleON();

      pExam->add(pItem);
   }

   // std::cerr << "\n" << *pExam << std::endl;

   // Item #3 ------------------------------------------------------------------
   {
      auto pItem = std::make_shared<GenItem>();
      pItem->setID("I3");
      auto pText = std::make_shared<GenText>(
         "pText",
         "Fusce in magna erat. Cras turpis est, semper "
         "lobortis dui. Phasellus urna turpis, eu ipsum sodales, "
         "venenatis sodales enim?");
      pText->setID("I3.text");
      pItem->addToStem(pText);

      auto pO1 = std::make_shared<GenOption>("03.1", "Sort Option 1.");
      auto pO2 =
         std::make_shared<GenOption>("03.2", "Sort Option 2...........");
      auto pO3 = std::make_shared<GenOption>("03.3", "Sort Option 3......");
      auto pO4 = std::make_shared<GenOption>("03.4", "Sort Option 4....");

      pItem->addToOptions(pO1);
      pItem->addToOptions(pO2);
      pItem->addToOptions(pO3);
      pItem->addToOptions(pO4, IS_CORRECT);
      pItem->sortOptions();

      pExam->add(pItem);
   }

   // std::cerr << "\n" << *pExam << std::endl;

   // Item #4a
   // ------------------------------------------------------------------
   {
      auto pItem = std::make_shared<GenItem>();
      pItem->setID("I4a");
      auto pText = std::make_shared<GenText>(
         "text",
         "Fusce in magna erat. Cras turpis est, semper "
         "lobortis dui. Phasellus urna turpis, eu ipsum sodales, "
         "venenatis sodales enim?");
      pText->setID("I3.text");
      pItem->addToStem(pText);

      auto pO1 = std::make_shared<GenOption>("03.1", "Sort Option 1.");
      auto pO2 =
         std::make_shared<GenOption>("03.2", "Sort Option 2............");
      auto pO3 = std::make_shared<GenOption>("03.3", "Sort Option 3......");
      auto pO4 = std::make_shared<GenOption>("03.4", "Sort Option 4....");

      pItem->addToOptions(pO1);
      pItem->addToOptions(pO2);
      pItem->addToOptions(pO3);
      pItem->addToOptions(pO4, IS_CORRECT);
      pItem->sortOptions();

      pExam->add(pItem);
   }

   // Item #4b
   // ------------------------------------------------------------------
   {
      auto pItem = std::make_shared<GenItem>();
      pItem->setID("I4b");
      auto pText = std::make_shared<GenText>(
         "text",
         "Fusce in magna erat. Cras turpis est, semper "
         "lobortis dui. Phasellus urna turpis, eu ipsum sodales, "
         "venenatis sodales enim?");
      pText->setID(pItem->getID() + ".text");
      pItem->addToStem(pText);

      auto pAPI = std::make_shared<GenAPI>("int", "multiply(int a, int b);",
                                           "Mutiplies two integers");
      pAPI->setID(pItem->getID() + ".code");
      pItem->addToStem(pAPI);
      auto pCodeText = std::make_shared<GenCodeText>("ct1", "c",
                                                     "int main()\n"
                                                     "{\n"
                                                     "   printf(\"Hello\");\n"
                                                     "}\n"
                                                     "\n");
      pItem->addToStem(pCodeText);

      auto pO1 = std::make_shared<GenOption>("04b.1", "Sort Option 1.");
      auto pO2 =
         std::make_shared<GenOption>("04b.2", "Sort Option 2............");
      auto pO3 = std::make_shared<GenOption>("04b.3", "Sort Option 3......");
      auto pO4 = std::make_shared<GenOption>("04b.4", "Sort Option 4....");

      pItem->addToOptions(pO1);
      pItem->addToOptions(pO2);
      pItem->addToOptions(pO3);
      pItem->addToOptions(pO4, IS_CORRECT);
      pItem->sortOptions();

      pExam->add(pItem);
   }

   // std::cerr << "\n" << *pExam << std::endl;

   auto p1 = genLogicFactory.create("LogicDiagramAON");
   p1->setID("LdAON1");
   pExam->add(p1);
  
   auto p2 = genLogicFactory.create("TwoC");
   p2->setID("TwoC1");
   p2->prepare();
   pExam->add(p2);
   
   auto p3 = genCFactory.create("NestedFor");
   p3->setID("NF1");
   p3->prepare();
   pExam->add(p3);

   std::cerr << "\n" << *pExam << std::endl;

   // Generate exam LaTeX text -------------------------------------------------
   pExam->generate(LaTeXfile);

   LOGI("Generating LaTeX file is ready");
}
