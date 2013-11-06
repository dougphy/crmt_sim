
/*  An Example ROOT macro to extract simulation information  */
/*  for plotting distributions of simulation variables.      */
/*  This macro assumes "afile.root" is in the output dir     */

{
  TFile *the_file = new TFile("../output/afile.root");
  TTree *the_tree = (TTree*)the_file->Get("SimulationTree");
  TH1D *hTrajX = new TH1D("hTrajX",";X Trajectory;Counts",100,1,0);
  TH1D *hAngXZ = new TH1D("hAngXZ",";Angle XZ;Counts",100,1,0);
  double Traj[3];
  double AngleXZ;
  for (int i = 0; i < the_tree->GetEntries(); i++) {
    the_tree->GetEntry(i);
    the_tree->SetBranchAddress("Traj",Traj);
    the_tree->SetBranchAddress("AngleXZ",&AngleXZ);
    hTrajX->Fill(Traj[0]);
    hAngXZ->Fill(AngleXZ);
  }
  TCanvas c1;
  hTrajX->Draw();
  TCanvas c2;
  hAngXZ->Draw();
}
