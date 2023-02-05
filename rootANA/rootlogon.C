void rootlogon() {
  printf("running my rootlogon...\n");
  gInterpreter->AddIncludePath("../src/"); // permite a ROOT saber onde estão os meus include files
  gSystem->CompileMacro("../src/point.C", "k O"); // compila a classe point
  gSystem->CompileMacro("../src/line.C", "k O"); // compila a classe line
}
