{
    
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    TCanvas *c1 = new TCanvas("c1","TISCA ACCIAIO con segnale BLU", 900, 600);
    TH1D *h1 = new TH1D("Histogram parameters","TISCA ACCIAIO con segnale BLU;# CH;Counts",1024,0,1023);
    
    in.open("tisca_acciaio-segnale_blu.mca");
    
    while (1) {
        in >> stringData;
        
        if(dataStop == false) {
            if(stringData == "<<END>>") {
                dataStop = true;
            }
        }
        
        if(dataStart && !dataStop) {
            numericData = stoi(stringData);
            if (!in.good()) break;
            h1->Fill(channel, numericData);
            channel++;
        }
        
        if(dataStart == false) {
            if(stringData == "<<DATA>>") {
                dataStart = true;
            }
        }
        
        in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if (!in.good()) break;
        nlines++;
    }
    in.close();
    
    h1->Draw();
    c1->SaveAs("tisca_acciaio_segnale_blu.pdf",".pdf");
    c1->SaveAs("tisca_acciaio_segnale_blu.root",".root");
}



