{
    
    ifstream in;
    
    Int_t rownumber , ch1 , ch2 , ch3 , ch4 , ch5;  //Identificativi colonne per input file .dat
    Double_t t1, t2, t3, t4, t5; //Identificativi tempi TDC
    Int_t nlines = 0;
    Double_t xmax, xmin, L = 11.621, c = 299792458, A, B, degree = (180/(TMath::Pi())), CHtoSEC = 0.25*TMath::Power(10,-9);   //Definisco L (lunghezza lato quadrato scintillatori), c (velocità della luce), A e B parametri eq. piano, degree per convertire radianti in gradi, CHtoSEC per convertire canali in secondi
    Double_t k = c/(2*L), A2, B2, C; //k è rapporto costante per abbreviare formule, A2 e B2 sono A e B al quadrato
    
    in.open("TDCquintupla_finale.dat");
    
    TCanvas *c1 = new TCanvas("c1","TDC Angular distribution", 1600, 1600);
    TH1F *h1 = new TH1F("Histogram and fit parameters","Theta distribution;Degrees;Counts",100,-5,95);
    TH1F *h2 = new TH1F("Histogram parameters","Phi distribution;Degrees;Counts",370,-185,185);

    TH1F *h3 = new TH1F("Histogram parameters","Time distribution;Delta time (s);Counts",1000,-2*TMath::Power(10,-7),2*TMath::Power(10,-7));
    
    while (1) {
        in >> rownumber >> ch1 >> ch2 >> ch3 >> ch4 >> ch5;
        in.ignore(100,'\n');
        if (!in.good()) break;
        t1 = ch1 * CHtoSEC;
        t2 = ch2 * CHtoSEC - 2.38574*TMath::Power(10,-9);
        t3 = ch3 * CHtoSEC - 1.18649*TMath::Power(10,-9);
        t4 = ch4 * CHtoSEC + 2.38574*TMath::Power(10,-9);
        t5 = ch5 * CHtoSEC + 1.18649*TMath::Power(10,-9);
        A = k*(t5-t3+t2-t4);
        B = k*(t2-t4-t5+t3);
        A2 = TMath::Power(A,2.);
        B2 = TMath::Power(B,2.);
        C = TMath::Sqrt(1 - A2 - B2);
        h1->Fill((TMath::ACos(C))*degree);
        h2->Fill((TMath::ATan2(B,A))*degree);
        h3->Fill(t3-t4-t2+t5);
        nlines++;
    }
    in.close();
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    
    c1->Divide(1,2);
    
    TF1 *fitFunction = new TF1("Fit function", "[0] * TMath::Sin((TMath::Pi()*x)/180) * TMath::Cos((TMath::Pi()*x)/180) * TMath::Exp(-[1]/TMath::Cos((TMath::Pi()*x)/180))", 0, 90);
    fitFunction->SetParNames("p0", "p1");
    fitFunction->SetParameters(1,8);
    
    
    //h1->SetMaximum(100);
    c1->cd(1);          //////////////////////
    h1->Fit(fitFunction,"R0FMV");
    h1->Draw();
    fitFunction->Draw("SAME");
    fitFunction->SetLineColor(2);
    fitFunction->SetLineWidth(3);
    fitFunction->SetLineStyle(10);
    h1->SetLabelSize( 0.05, "X" );  //Axis settings
    h1->SetTitleOffset(1, "X");
    h1->SetTitleSize(0.05, "X");
    c1->cd(2);          //////////////////////
    h2->Draw();

    h2->SetLabelSize( 0.05, "X" );  //Axis settings
    h2->SetTitleOffset(1, "X");
    h2->SetTitleSize(0.05, "X");
    c1->SaveAs("Angular distribution.pdf","pdf");
    
    TCanvas *c2 = new TCanvas("c2","TDC Time distribution / Shower width", 1600, 400);
    h3->Draw();
    h3->SetLabelSize( 0.05, "X" );  //Axis settings
    h3->SetTitleOffset(1, "X");
    h3->SetTitleSize(0.05, "X");
    c2->SaveAs("Time distribution.pdf","pdf");
    
    Double_t width = c * (h3->GetStdDev())/2;
    Double_t widthError = c * (h3->GetStdDevError())/2;

    cout << "Shower width " << width << " +- " << widthError << endl;
}


