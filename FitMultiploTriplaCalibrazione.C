{
    ifstream in;
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, data = 0;
    
    TCanvas *c1 = new TCanvas("c1","SCA segnale BLU", 1600, 1200);
    TH1F *h1 = new TH1F("Histogram parameters","Americio, Curio, Nettunio;# CH;Counts",1024,0,1023);
    
    in.open("Americio_Curio_Nettunio_1000secondi_-200V.mca");
    
    while (1) {
        if(nlines >= 14 and nlines <= 1037) {
            in >> data;
            if (!in.good()) break;
            h1->Fill(channel, data);
            h1->SetBinError(channel+1,TMath::Sqrt(data));
            channel++;
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if (!in.good()) break;
        nlines++;
    }
    in.close();
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    gStyle->SetStatH(0.07); gStyle->SetStatW(0.12);
    
    h1->SetMinimum(0);
    Double_t par[12];
    TF1 *g0    = new TF1("g1","gaus",640,660);
    TF1 *g1    = new TF1("g1","gaus",664,680);
    TF1 *g2    = new TF1("g2","gaus",767,780);
    TF1 *g3    = new TF1("g3","gaus",810,826);
    TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)+gaus(9)",630,840);
    total->SetLineColor(2);
    h1->Fit(g0,"R","goff");
    h1->Fit(g1,"R+","goff");
    h1->Fit(g2,"R+","goff");
    h1->Fit(g3,"R+","goff");
    g0->GetParameters(&par[0]);
    g1->GetParameters(&par[3]);
    g2->GetParameters(&par[6]);
    g3->GetParameters(&par[9]);
    total->SetParameters(par);
    total->SetParNames("Constant(1)","Mean(1)","Sigma(1)","Constant(2)","Mean(2)","Sigma(2)","Constant(3)","Mean(3)","Sigma(3)","Constant(4)","Mean(4)");
    total -> SetParName(11,"Sigma(4)");	     
    h1->Fit(total,"R");
    c1->SaveAs("FitMultiploTriplaCalibrazione.pdf",".pdf");
    c1->SaveAs("FitMultiploTriplaCalibrazione.root",".root");
}
