//////////////////////////////////////////////////////
// DO NOT EDIT THIS FILE

#include "student_code_2.h"
#include "test_framework.h"
#include <string>
#include <vector>

const char *smallDataset = "small_problem_set_2.in";
const char *largeDataset = "large_problem_set_2.in";

const char *helpMsg = "Please, indicate which problem set to use.\n\n"
                      "For small problem set, type: ./problem_solver_2 small\n"
                      "For large problem set, type: ./problem_solver_2 large\n";

const char *strNotice = "##################################\n"
                        "# Do not edit this file!\n"
                        "##################################\n";

constexpr int problem_set_id = 2;

struct ProblemN2 : public TestFramework::BasicProblem {
  std::vector<int> sale;
  std::vector<int> before;
  std::vector<int> after;
  int k;
};

int MinCostHelper(const std::vector<int> &sale, const std::vector<int> &before,
                  const std::vector<int> &after, int k) {
  size_t giftCount = sale.size();
  bool areArraySizesEqual =
      (giftCount == before.size()) && (giftCount == after.size());

  TestFramework::ExitIfConditionFails(areArraySizesEqual,
                                      "Arrays sale, befor, and after"
                                      "have different sizes. "
                                      "Please, check input files.");

  std::vector<Price> giftPrices(giftCount);
  for (size_t i = 0; i < giftCount; ++i) {
    giftPrices[i] = {sale[i], before[i], after[i]};
  }

  return MinCost(giftPrices, k);
}

int main(int argc, char *argv[]) {
  using namespace TestFramework;

  static_assert(GetTestFrameworkVersion() == 8,
                "TestFramework version 8 is required."
                "Please, update test_framework.h.");

  if ((argc != 2) && (argc != 3)) {
    std::cout << helpMsg;
  }

  std::string firstArg(DefaultProblemSet());

  if (argc >= 2) {
    firstArg = argv[1];
  } else {
    std::cout << "\nUsing the default problem set: " << firstArg;
  }

  ExitIfConditionFails((firstArg == "small") || (firstArg == "large"),
                       "Unknown problem set.");
  bool bSmallDataset = (firstArg == "small");

  std::cout << std::endl << "Problem set #" << problem_set_id << ". ";

  ProblemSetHeader header;
  RecordAdapter<ProblemSetHeader> psAdapter(header);
  AddDefaultProblemSetColumns(psAdapter);

  std::vector<ProblemN2> problems;
  TableAdapter<ProblemN2> prAdapter(problems);
  AddDefaultProblemColumns(prAdapter);

  AddColumn<ProblemN2>(prAdapter, "sale", &ProblemN2::sale);
  AddColumn<ProblemN2>(prAdapter, "before", &ProblemN2::before);
  AddColumn<ProblemN2>(prAdapter, "after", &ProblemN2::after);
  AddColumn<ProblemN2>(prAdapter, "k", &ProblemN2::k);

  BasicYamlParser parser(dynamic_cast<ITable *>(&psAdapter),
                         dynamic_cast<ITable *>(&prAdapter));

  const char *inputFilename = bSmallDataset ? smallDataset : largeDataset;
  std::cout << "File: " << inputFilename << ".\n";

  parser.ParseFile(inputFilename, true);
  PreprocessProblemSet(problem_set_id, problems, header);

  for (auto &theProblem : problems) {
    theProblem.student_answer = MinCostHelper(
        theProblem.sale, theProblem.before, theProblem.after, theProblem.k);
  }

  ProcessResults(problems, header);

  std::cout << "Don't forget to submit your "
               "source code on Canvas.";

  std::cout << "\nRunning time: ";
  std::cout << header.time << "ms";
  std::cout << std::endl << std::endl;
  std::cout << std::endl << std::endl;

  if (argc == 3) {
    const char *outputFilename = argv[2];
    std::cout << "Generating a report. ";
    std::cout << "The report is saved in file '";
    std::cout << outputFilename << "'.\n";
    TableAdapter<ProblemN2> prOutAdapter(problems);
    AddDefaultProblemColumnsForOutput(prOutAdapter);

    WriteTableToFile(outputFilename, &psAdapter, 
                     &prOutAdapter, true,
                     strNotice);
  }

  return 0;
}
