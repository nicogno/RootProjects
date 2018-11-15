{
    gROOT->SetBatch(kTRUE);
    
    ifstream in, inputFileNames;
    char output[100];
    vector <string> FileNames;
    
    string titolo;
    inputFileNames.open("filenames.dat");   //Lettura file con nomi files
    
    while (!inputFileNames.eof()) {
        inputFileNames >> output;
        FileNames.push_back(output);
    }
    string CH1 = "CH1", CH2 = "CH2";
    Int_t x,y,z;
    Int_t nlines = 0;
    int nbins;
    int k = 0, j = 0, binmin = 0, binmax = 0;
    double xmax, xmin;
    TCanvas *c1 = new TCanvas("c1","Test Canvas", 1200, 600);
    const char *HistName;
    const char *HistTitle[100];
    
    int const numberOfFiles = FileNames.size();
    
    TH1D *histoArray[14];
    
    gStyle->SetOptFit(0111);
    gStyle->SetOptStat(1111);
    gStyle->SetStatH(0.15);
    gStyle->SetStatW(0.20);
    
    for(int fileIndex = 0; fileIndex<FileNames.size(); fileIndex++) {
        HistName = FileNames[fileIndex].c_str();
        HistTitle[fileIndex] = FileNames[fileIndex].substr(0, FileNames[fileIndex].size()-4).c_str();
        
        in.open(HistName);
        x = 0, y = 0, z = 0, nlines = 0;
        
        histoArray[fileIndex] = new TH1D("Histogram and Fit parameters","",1000,0,1000);
        
        if (FileNames[fileIndex].find(CH2) < std::string::npos)
            {

                while (1) {
                    in >> x >> y >> z ;
                    in.ignore(100,'\n');
                    if (!in.good()) break;
                    histoArray[fileIndex]->Fill(z);
                    nlines++;
                }
                histoArray[fileIndex]->Fit("gaus");
                
                nbins = histoArray[fileIndex] -> GetNbinsX();
                k = 0, j = 0, binmin = 0, binmax = 0;
                
                while(j < nbins && k == 0) {
                    if (histoArray[fileIndex]->GetBinContent(j) > 0) {
                        binmin = j;
                        k = 1;
                    }
                    j++;
                }
                
                j = nbins, k = 0;
                
                while(j > 0 && k == 0) {
                    if (histoArray[fileIndex]->GetBinContent(j) > 0) {
                        binmax = j;
                        k = 1;
                    }
                    j--;
                }
                
                xmax = (histoArray[fileIndex]->GetXaxis()->GetBinCenter(binmax)) + 5;
                xmin = (histoArray[fileIndex]->GetXaxis()->GetBinCenter(binmin)) - 5;
                histoArray[fileIndex]->GetXaxis()->SetRangeUser(xmin, xmax);
                
                histoArray[fileIndex]->SetMaximum((histoArray[fileIndex]->GetFunction("gaus")->GetParameter(0))+10);
                

                histoArray[fileIndex]->Draw("h");
                
                /*
                //Stats box editing|
                c1->Update();
                TPaveStats *ps = (TPaveStats*)c1->GetPrimitive("stats");
                ps->SetX1NDC(0.85);
                ps->SetX2NDC(0.99);
                ps->SetY1NDC(0.70);
                ps->SetY2NDC(0.95);
                ps->SetName("mystats");
                histoArray[fileIndex]->SetStats(0);
                c1->Modified();
                ////////////////////*/
                
                histoArray[fileIndex]->GetXaxis()->SetTitle("# Channels");
                histoArray[fileIndex]->GetYaxis()->SetTitle("Counts");
                
                titolo = HistName;
                
                titolo = titolo.append(".pdf");
                
                c1->SaveAs(titolo.c_str(),"pdf");
                
                
            } else if(FileNames[fileIndex].find(CH1) < std::string::npos) {
                
                while (1) {
                    in >> x >> y >> z ;
                    in.ignore(100,'\n');
                    if (!in.good()) break;
                    histoArray[fileIndex] -> Fill(y);
                    nlines++;
                }
                histoArray[fileIndex]->Fit("gaus");
            
                nbins = histoArray[fileIndex] -> GetNbinsX();
                k = 0, j = 0, binmin = 0, binmax = 0;
                
                while(j < nbins && k == 0) {
                    if (histoArray[fileIndex]->GetBinContent(j) > 0) {
                        binmin = j;
                        k = 1;
                    }
                    j++;
                }
                
                j = nbins, k = 0;
                
                while(j > 0 && k == 0) {
                    if (histoArray[fileIndex]->GetBinContent(j) > 0) {
                        binmax = j;
                        k = 1;
                    }
                    j--;
                }
                
                xmax = (histoArray[fileIndex]->GetXaxis()->GetBinCenter(binmax)) + 5;
                xmin = (histoArray[fileIndex]->GetXaxis()->GetBinCenter(binmin)) - 5;
                histoArray[fileIndex]->GetXaxis()->SetRangeUser(xmin, xmax);
                
                histoArray[fileIndex]->SetMaximum((histoArray[fileIndex]->GetFunction("gaus")->GetParameter(0))+10);
                
                
                
                histoArray[fileIndex]->Draw("h");
                
                //Stats box editing
                /*c1->Update();
                TPaveStats *ps = (TPaveStats*)c1->GetPrimitive("stats");
                ps->SetX1NDC(0.85);
                ps->SetX2NDC(0.99);
                ps->SetY1NDC(0.70);
                ps->SetY2NDC(0.95);
                ps->SetName("mystats");
                histoArray[fileIndex]->SetStats(0);
                c1->Modified();
                ////////////////////*/
                
                histoArray[fileIndex]->GetXaxis()->SetTitle("# Channels");
                histoArray[fileIndex]->GetYaxis()->SetTitle("Counts");
                
                titolo = HistName;
                
                titolo = titolo.append(".pdf");
                
                c1->SaveAs(titolo.c_str(),"pdf");
            }
        in.close();
    }
}

