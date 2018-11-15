#include <iostream>
#include "TString.h"
#include "Rete.h"
#include "Ambiente.h"
#include "Persona.h"
#include "TSystem.h"


void compyle(TString myopt="fast"){
    TString opt;
    if(myopt.Contains("force")) opt="kfg";
    else opt="kg";
    gSystem->CompileMacro("Rete.cxx",opt.Data());
    gSystem->CompileMacro("Persona.cxx",opt.Data());
    gSystem->CompileMacro("Ambiente.cxx",opt.Data());
    gSystem->CompileMacro("Main.cxx",opt.Data());
}
