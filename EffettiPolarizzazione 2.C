{
    gROOT->SetBatch(kTRUE);     //Per non stampare ogni volta il canvas sullo schermo
    gErrorIgnoreLevel = kWarning;   //Per rimuovere i messaggi di info sul terminale
    ifstream in, inputFilenames;    //Conterranno rispettivamente il file con i dati e il file con i nomi dei .mca da leggere
    
    const Int_t CHANNELS = 1024;
    Int_t nlines = 0, channel = 0, numericData = 0;
    bool dataStart = false, dataStop = false;
    string stringData = "", titleTemp;  //titleTemp serve per poter modificare il nome del file e usarlo come titolo
    char name[100] = "";
    vector <string> FileNamesVector;        //Vettore che conterrà i nomi dei file da leggere
    
    TCanvas *c1 = new TCanvas("c1","Canvas", 1200, 600);
    
    inputFilenames.open("files.dat");
    
    while (!inputFilenames.eof()) {         //Leggo tutto il file contenente i nomi dei file con i dati
        inputFilenames >> name;
        FileNamesVector.push_back(name);
    }
    
    int const numberOfFiles = FileNamesVector.size();
    
    TH1D *histoArray[17];
    
    gStyle->SetOptFit(0111);    gStyle->SetOptStat(1111);   gStyle->SetStatH(0.15); gStyle->SetStatW(0.20); //Setting stile stat box
    
    TF1 *g0;
    
    for(int fileIndex = 0; fileIndex<FileNamesVector.size(); fileIndex++) {     //Lettura files .mca
        
        nlines = 0, channel = 0, numericData = 0, dataStart = false, dataStop = false;      //Setto le variabili ai valori di default all'inizio di ogni ciclo
        
        ostringstream histogramNameStream;  //Conterrà i nomi degli istogrammi
        
        in.open(FileNamesVector[fileIndex].c_str());    //Apro il file da leggere contenente i dati
        
        titleTemp = FileNamesVector[fileIndex];         //Uso titleTemp in modo tale che il titolo originale del file sia poi utilizzabile al fondo per creare il .pdf
        
        std::replace( titleTemp.begin(), titleTemp.end(), '_', ' ');    //Rimpiazzo nel titolo gli underscores con gli spazi
        if (titleTemp.find("+") < std::numeric_limits<std::streamsize>::max()) {titleTemp.replace(titleTemp.find("+"),1," +");} //Aggiungo nei titoli uno spazio quando trova il +
        if (titleTemp.find("-") < std::numeric_limits<std::streamsize>::max()) {titleTemp.replace(titleTemp.find("-"),1," -");} //Aggiungo nei titoli uno spazio quando trova il -
        
        histogramNameStream << titleTemp.substr(0, titleTemp.size()-4) << ";Energy (KeV);Counts";   //Rimuovo l'estensione .dati dal fondo del titolo e inserisco i titoli degli assi
        
        histoArray[fileIndex] = new TH1D("Histogram parameters",histogramNameStream.str().c_str(),1024,0,1023*7.174);     //Creazione istogramma
        
        while (1) {
            in >> stringData;
            
           if(dataStop == false) {          //Controllo se questa è l'ultima riga e quindi va fermata l'acquisizione
                if(stringData == "<<END>>") {
                    dataStop = true;
                }
            }
            
            if(dataStart && !dataStop) {        //Lettura dati e fill grafici
                numericData = stoi(stringData);
                if (!in.good()) break;
                histoArray[fileIndex]->Fill(channel*7.174, numericData);
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
        
        /*g0    = new TF1("g0","gaus",histoArray[fileIndex]->GetMean()-histoArray[fileIndex]->GetStdDev(),histoArray[fileIndex]->GetMean()+2*histoArray[fileIndex]->GetStdDev());
        histoArray[fileIndex]->Fit("g0","R");
        
        histoArray[fileIndex]->GetXaxis()->SetRangeUser(g0->GetParameter(1)-7*g0->GetParameter(2),g0->GetParameter(1)+7*g0->GetParameter(2));*/
        
        histoArray[fileIndex]->Draw();
        
        ostringstream histogramPDFStream, histogramROOTStream;
        histogramPDFStream << FileNamesVector[fileIndex].substr(0, FileNamesVector[fileIndex].size()-4).c_str() << ".pdf";      //Creo il titolo del file .pdf in cui verrà salvato il grafico
        histogramROOTStream << FileNamesVector[fileIndex].substr(0, FileNamesVector[fileIndex].size()-4).c_str() << ".root";      //Creo il titolo del file .root in cui verrà salvato il grafico
        c1->SaveAs(histogramPDFStream.str().c_str(),".pdf");
        c1->SaveAs(histogramROOTStream.str().c_str(),".root");
    }
}

