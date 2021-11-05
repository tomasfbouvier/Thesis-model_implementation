#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

void get_weights(){

    // opening file
    TFile* inputFile = TFile::Open("AnalysisResults.root", "READ");
    if(!inputFile || !inputFile->IsOpen()) { printf("Problem with the input file \n"); return;}


    // find and open tprofile with <<2>> (this is NOT v2)
    inputFile->cd("FlowExampleTask");
    TList* inputList = (TList*) gDirectory->Get("Output");
    
    
    TTree*  MyTree = (TTree*)inputList->FindObject("T");
    
    TTreeReader myReader(MyTree);
    
    TTreeReaderValue<Int_t> eventn(myReader, "eventn");
    // The branch "py" contains floats, too; access those as myPy.
    TTreeReaderValue<Float_t> px(myReader, "momentum.px");
    TTreeReaderValue<Float_t> py(myReader, "momentum.py");
    TTreeReaderValue<Float_t> pz(myReader, "momentum.pz");
    //!TTreeReaderValue<Float_t> myPz(myReader, "pz");
    
    ofstream myfile;
    myfile.open ("example.csv");
    MyTree->Print();
    
    
    while (myReader.Next()) {
         // Just access the data as if myPx and myPy were iterators (note the '*'
         // in front of them):
        myfile<<*eventn<<","<<*px<<","<<*py<<","<<*pz<<"\n";
//!cout<<*eventn<<"\n";
    }
     
    myfile.close();
   /*
    
    Double_t Nmax= fHistPhi->GetBinContent(fHistPhi->GetMaximumBin());
    
    for(Int_t i=0; i< fHistWeightsPhi->GetNbinsX()+2; i++){
        Double_t content= fHistPhi->GetBinContent(i);
        if(content>0){
            fHistWeightsPhi->SetBinContent(i, Nmax/content);
        }
        else{
            fHistWeightsPhi->SetBinContent(i, 1);
        }
        
    }
    
    new TCanvas();
     
    fHistWeightsPhi->Draw();
    
    TFile outputFile("/Users/tomasfernandezbouvier/Desktop/alice/Thesis-training-/Weights.root","RECREATE");
    fHistWeightsPhi->Write();

   // Closing the ROOT file.
    outputFile.Close();
    
    TList* weights = new TList();
    weights->SetOwner(kTRUE);
    weights->Add(fHistWeightsPhi);

    TH1D* weightsPlaceHolder = (TH1D*)fHistWeightsPhi->Clone("weightsPlaceHolder");
    weightsPlaceHolder->Scale(3.);
    weights->Add(weightsPlaceHolder);

    TFile* output = new TFile("weight.root", "RECREATE");
    weights->Write("weightsList",TObject::kSingleKey+TObject::kOverwrite);
*/
    
    
    
    return;
}
