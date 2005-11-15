/*
 * \file EBPedPreSampleClient.cc
 * 
 * $Date: 2005/11/15 20:11:34 $
 * $Revision: 1.15 $
 * \author G. Della Ricca
 *
*/

#include <DQM/EcalBarrelMonitorClient/interface/EBPedPreSampleClient.h>

EBPedPreSampleClient::EBPedPreSampleClient(const edm::ParameterSet& ps, MonitorUserInterface* mui){

  mui_ = mui;

  Char_t histo[50];

  for ( int i = 0; i < 36; i++ ) {

    h01[i] = 0;

  }

}

EBPedPreSampleClient::~EBPedPreSampleClient(){

  this->unsubscribe();

}

void EBPedPreSampleClient::beginJob(const edm::EventSetup& c){

  cout << "EBPedPreSampleClient: beginJob" << endl;

  ievt_ = 0;

}

void EBPedPreSampleClient::beginRun(const edm::EventSetup& c){

  cout << "EBPedPreSampleClient: beginRun" << endl;

  jevt_ = 0;

  this->subscribe();

  for ( int i = 0; i < 36; i++ ) {

    if ( h01[i] ) delete h01[i];

  }

}

void EBPedPreSampleClient::endJob(void) {

  cout << "EBPedPreSampleClient: endJob, ievt = " << ievt_ << endl;

}

void EBPedPreSampleClient::endRun(EcalCondDBInterface* econn, RunIOV* runiov, RunTag* runtag) {

  cout << "EBPedPreSampleClient: endRun, jevt = " << jevt_ << endl;

  if ( jevt_ == 0 ) return;

  EcalLogicID ecid;
//  MonPedestalsDat p;
//  map<EcalLogicID, MonPedestalsDat> dataset;

  cout << "Writing MonPedPreSampleDatObjects to database ..." << endl;

  float n_min_tot = 1000.;
  float n_min_bin = 50.;

  for ( int ism = 1; ism <= 36; ism++ ) {

    float num01;
    float mean01;
    float rms01;

    for ( int ie = 1; ie <= 85; ie++ ) {
      for ( int ip = 1; ip <= 20; ip++ ) {

        num01  = -1.;
        mean01 = -1.;
        rms01  = -1.;

        bool update_channel = false;

        if ( h01[ism-1] && h01[ism-1]->GetEntries() >= n_min_tot ) {
          num01 = h01[ism-1]->GetBinEntries(h01[ism-1]->GetBin(ie, ip));
          if ( num01 >= n_min_bin ) {
            mean01 = h01[ism-1]->GetBinContent(h01[ism-1]->GetBin(ie, ip));
            rms01  = h01[ism-1]->GetBinError(h01[ism-1]->GetBin(ie, ip));
            update_channel = true;
          }
        }

        if ( update_channel ) {

          if ( ie == 1 && ip == 1 ) {

            cout << "Inserting dataset for SM=" << ism << endl;

            cout << "G01 (" << ie << "," << ip << ") " << num01  << " "
                                                       << mean01 << " "
                                                       << rms01  << endl;
          }

//          p.setPedMeanG1(mean01);
//          p.setPedRMSG1(rms01);

//          p.setTaskStatus(1);

          if ( econn ) {
            try {
              ecid = econn->getEcalLogicID("EB_crystal_index", ism, ie-1, ip-1);
//              dataset[ecid] = p;
            } catch (runtime_error &e) {
              cerr << e.what() << endl;
            }
          }

        }

      }
    }

  }

  if ( econn ) {
    try {
      cout << "Inserting dataset ... " << flush;
//      econn->insertDataSet(&dataset, runiov, runtag );
      cout << "done." << endl;
    } catch (runtime_error &e) {
      cerr << e.what() << endl;
    }
  }

}

void EBPedPreSampleClient::subscribe(void){

  // subscribe to all monitorable matching pattern
  mui_->subscribe("*/EcalBarrel/EBPedPreSampleTask/Gain01/EBPT pedestal PreSample SM*");

}

void EBPedPreSampleClient::subscribeNew(void){

  // subscribe to new monitorable matching pattern
  mui_->subscribeNew("*/EcalBarrel/EBPedPreSampleTask/Gain01/EBPT pedestal PreSample SM*");

}

void EBPedPreSampleClient::unsubscribe(void){

  // unsubscribe to all monitorable matching pattern
  mui_->unsubscribe("*/EcalBarrel/EBPedPreSampleTask/Gain01/EBPT pedestal PreSample SM*");

}

void EBPedPreSampleClient::analyze(const edm::Event& e, const edm::EventSetup& c){

  ievt_++;
  jevt_++;
  if ( ievt_ % 10 == 0 )  
  cout << "EBPedPreSampleClient: ievt/jevt = " << ievt_ << "/" << jevt_ << endl;

  this->subscribeNew();

  Char_t histo[150];

  MonitorElement* me;
  MonitorElementT<TNamed>* ob;

  for ( int ism = 1; ism <= 36; ism++ ) {

    if ( h01[ism-1] ) delete h01[ism-1];
    h01[ism-1] = 0;
    sprintf(histo, "Collector/FU0/EcalBarrel/EBPedPreSampleTask/Gain01/EBPT pedestal PreSample SM%02d G01", ism);
    me = mui_->get(histo);
    if ( me ) {
      cout << "Found '" << histo << "'" << endl;
      ob = dynamic_cast<MonitorElementT<TNamed>*> (me);
      if ( ob ) h01[ism-1] = dynamic_cast<TProfile2D*> ((ob->operator->())->Clone());
    }

  }

}

void EBPedPreSampleClient::htmlOutput(int run, string htmlDir){

  cout << "Preparing EBPedPreSampleClient html output ..." << endl;

  ofstream htmlFile;

  htmlFile.open((htmlDir + "EBPedPreSampleClient.html").c_str());


  htmlFile.close();

}

