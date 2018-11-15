{
    
    ifstream in;
    
    Int_t rownumber , ch1 , ch2 , ch3 , ch4 , ch5;  //Identificativi colonne per input file .dat
    Double_t t1, t2, t3, t4, t5, t21, t31, t41, t51; //Identificativi tempi TDC
    Int_t nlines = 0;
    Double_t xmax, xmin, CHtoSEC = 0.25*TMath::Power(10,-9), Delta24, Delta35;
    
    in.open("TDCquintupla_finale.dat");
    
    TCanvas *c1 = new TCanvas("c1","TDC Time distributions", 1600, 1600);
    TH1F *h1 = new TH1F("Histogram parameters","t2 - t1;Delta time (s);Counts",1000,-2*TMath::Power(10,-7),2*TMath::Power(10,-7));
    TH1F *h2 = new TH1F("Histogram parameters","t3 - t1;Delta time (s);Counts",1000,-2*TMath::Power(10,-7),2*TMath::Power(10,-7));
    TH1F *h3 = new TH1F("Histogram parameters","t4 - t1;Delta time (s);Counts",1000,-2*TMath::Power(10,-7),2*TMath::Power(10,-7));
    TH1F *h4 = new TH1F("Histogram parameters","t5 - t1;Delta time (s);Counts",1000,-2*TMath::Power(10,-7),2*TMath::Power(10,-7));
    
    while (1) {
        in >> rownumber >> ch1 >> ch2 >> ch3 >> ch4 >> ch5;
        in.ignore(100,'\n');
        if (!in.good()) break;
        t1 = ch1 * CHtoSEC;
        t2 = ch2 * CHtoSEC;
        t3 = ch3 * CHtoSEC;
        t4 = ch4 * CHtoSEC;
        t5 = ch5 * CHtoSEC;
        t21 = t2 - t1;
        t31 = t3 - t1;
        t41 = t4 - t1;
        t51 = t5 - t1;
        h1 -> Fill(t21);
        h2 -> Fill(t31);
        h3 -> Fill(t41);
        h4 -> Fill(t51);
        nlines++;
    }
    in.close();
   
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    
    //Stat box position, height and width
    //gStyle->SetStatX(.9);
    //gStyle->SetStatY(.9);
    gStyle->SetStatH(0.10);
    gStyle->SetStatW(0.40);
    gStyle->SetTitleFontSize(0.1);  //Histogram titles size
    
    c1->Divide(2,2);
    
    
    c1->cd(1);          //////////////////////
    h1->Draw();
    h1->SetLabelSize( 0.05, "X" );  //Axis settings
    h1->SetTitleOffset(1.3, "X");
    h1->SetTitleSize(0.04, "X");
    c1->cd(2);          //////////////////////
    h2->Draw();
    h2->SetLabelSize( 0.05, "X" );  //Axis settings
    h2->SetTitleOffset(1.3, "X");
    h2->SetTitleSize(0.04, "X");
    c1->cd(3);          //////////////////////
    h3->Draw();
    h3->SetLabelSize( 0.05, "X" );  //Axis settings
    h3->SetTitleOffset(1.3, "X");
    h3->SetTitleSize(0.04, "X");
    c1->cd(4);          //////////////////////
    h4->Draw();
    h4->SetLabelSize( 0.05, "X" );  //Axis settings
    h4->SetTitleOffset(1.3, "X");
    h4->SetTitleSize(0.04, "X");
    
    Delta24 = (h1 ->GetMean() - h3->GetMean() )/2;
    Delta35 = (h2 ->GetMean() - h4->GetMean() )/2;
    
    cout << "Delta24 " << Delta24 << endl;
    cout << "Delta35 " << Delta35 << endl;
    
    c1->SaveAs("DeltaTimes.pdf","pdf");
}


