#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

void trial(){
    /*
    TTree *t = new TTree("t", "tree from selection.csv");
    t->ReadFile("selection.csv","");
    
    t->Draw();
    */
    
    TFile* inputFile = TFile::Open("selection.root", "READ");
    if(!inputFile || !inputFile->IsOpen()) { printf("Problem with the input file \n"); return;}


    // find and open tprofile with <<2>> (this is NOT v2)
    TTree* MyTree = (TTree*) gDirectory->Get("tree1");
    TTreeReader myReader(MyTree);
    TTreeReaderValue<Double_t>eventn(myReader, "branch1");
    
    while (myReader.Next()) {
         // Just access the data as if myPx and myPy were iterators (note the '*'
         // in front of them):
        cout<<*eventn<<"\n";
    }
    
    
    return;
}
