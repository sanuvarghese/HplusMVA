import ROOT

ROOT.gInterpreter.Declare('''
using Vec_t = const ROOT::RVec<float>&;
float Compute_mjj(float jetChadPt,float jetChadEta,float jetChadPhi,float jetChadEnergy,float jetShadPt,float jetShadEta,float jetShadPhi,float jetShadEnergy) {
    const ROOT::Math::PtEtaPhiEVector cjet(jetChadPt, jetChadEta, jetChadPhi, jetChadEnergy);
    const ROOT::Math::PtEtaPhiEVector sjet(jetShadPt, jetShadEta, jetShadPhi, jetShadEnergy);
    return (cjet + sjet).M();
}
''')
ROOT.gInterpreter.Declare('''
namespace Helper {
using Vec_t = const ROOT::RVec<float>&;
auto  add_p4 = [](float pt, float eta, float phi, float energy) {
   return ROOT::Math::PtEtaPhiEVector(pt, eta, phi, energy);
};
}
''')
ROOT.gInterpreter.Declare('''
namespace Helper {

using Vec_t = const ROOT::RVec<float>&;
auto  Boost_to_rftest = [](auto cjet,auto sjet,auto j1) {
     auto Higgs = cjet + sjet;
     auto Higgs_rf = ROOT::Math::Boost(Higgs.BoostToCM());
     return Higgs_rf(j1);
     
};
}

''')
ROOT.gInterpreter.Declare('''
namespace Helper {

auto CosVector_test = [](auto cjet,auto sjet,auto super1,auto super2,auto super3,float CvsL_j1,float CvsL_j2){

     auto j1 = Helper::Boost_to_rftest(cjet,sjet,super1);
     auto j2 = Helper::Boost_to_rftest(cjet,sjet,super2);
      auto j3 = Helper::Boost_to_rftest(cjet,sjet,super3);
     
     auto j1_rf = j1.Vect();
     auto j2_rf = j2.Vect();
     auto j3_rf = j3.Vect();
     auto j1_u = j1_rf.Unit() ;
     auto j2_u = j2_rf.Unit() ;
     auto j3_u = j3_rf.Unit() ;
     if(CvsL_j1 >= CvsL_j2){
     return j1_u.Dot(j2_u);
     }else{return j3_u.Dot(j2_u); }
    
     
     
     
     
};
     
     
     
     
}


''')
ROOT.gInterpreter.Declare('''

template <typename T>

float DeltaPhi(T v1, T v2, const T c = M_PI)
{
    auto r = std::fmod(v2 - v1, 2.0 * c);
    if (r < -c) {
        r += 2.0 * c;
    }
    else if (r > c) {
        r -= 2.0 * c;
    }
    return r;
}


''')
ROOT.gInterpreter.Declare('''

using Vec_t = const ROOT::RVec<float>&;
float  metPhi(float ptx,float pty) {
   return TMath::ATan(pty/ptx);
};

''')
