void rootlogon() {
  printf("running my rootlogon...\n");
  gInterpreter->AddIncludePath("../src/"); // permite a ROOT saber onde estão os meus include files
  gSystem->CompileMacro("../src/DataReader.C", "k O"); // compila a classe datareader
  gSystem->CompileMacro("../src/DataManip.C", "k O"); // compila a classe datamanip
}