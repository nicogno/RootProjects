{
    
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData;
    
    TCanvas *c1 = new TCanvas("c1","AmericioPicchiTempo+50V", 900, 600);
    TH1D *h1 = new TH1D("Histogram parameters","Americio spostamento picchi con il tempo (+50V);# CH;Counts",1024,0,1023);
    
    in.open("AmericioPicchiTempo+50V.mca");
    
    while (1) {
        in >> stringData;
        
       if(dataStop == false) {          //Controllo se questa è l'ultima riga e quindi va fermata l'acquisizione
            if(stringData == "<<END>>") {
                dataStop = true;
            }
        }
        
        if(dataStart && !dataStop) {
            numericData = stoi(stringData);
            if (!in.good()) break;
            h1->Fill(channel, numericData);
            //h1->SetBinError();
            channel++;
        }
        
        if(dataStart == false) {        //Controllo se dalla prossima riga si pò iniziare l'acquisizione dei dati
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
    c1->SaveAs("AmericioPicchiTempo+50V.pdf",".pdf");
    c1->SaveAs("AmericioPicchiTempo+50V.root",".root");
}

