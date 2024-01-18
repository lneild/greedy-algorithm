///////////////////////////////////////////////
// You need to
//    1. Carefully read the instructions.
//    2. Implement function MinCost.
//    3. Compile your code.
//    4. Run the executable on small and large
//       unit tests.
//    5. Test and debug your code. 
//       Make sure that your program does not 
//       have any memory leaks.
//    6. Remove all commented out code. 
//       Double check that your program does
//       not print any debug information on 
//       the screen.
//    7. Submit your source code 
//       ("student_code_2.h") on Canvas.
///////////////////////////////////////////////

//required libraries
#include <string>
#include <vector>
#include <array>
#include <algorithm>

//you can include standard C++ libraries here
struct Price
{
   int sale {0};
   int after {0};
   int before {0};
   // add fields
   int save {0}; 
   int bestNonSale {0};
};


std::string DefaultProblemSet()
{
    return "small";
}

int MinCost(std::vector<Price>& giftPrices, int k, int id)
{
   for (Price& p : giftPrices) {
      p.bestNonSale = std::min(p.before, p.after);
      p.save = std::min(p.before-p.sale, p.after-p.sale);
   }

   // sort by the savings:
   std::sort(giftPrices.begin(), giftPrices.end(), [](const Price &elem1, const Price &elem2) {
        return elem1.save > elem2.save;
   });
   int spent=0;
   int i=0;

   for (Price& p: giftPrices){
      if (p.bestNonSale <= p.sale) {
         spent+=p.bestNonSale;
      }
      else{
         if(i<k){
            spent+=p.sale;
            i++;
         } 
         else{
            spent+=p.bestNonSale;
         }
      }
   }
   return spent;
}

