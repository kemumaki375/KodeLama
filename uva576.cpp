// solution for uva576 ~ https://onlinejudge.org/external/5/576.pdf
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std ;

bool isVowel(string x) {
     if ( x == "a" || x == "e" || x == "i" || x == "u" || x == "o" || x == "y" ) {
        return true ;   
     }
     return false ;
}

int hNum[4]  ; // Jumlah haiku
int line     ; // Counter line sekarang

string dfa(string w, int state, int lastV = 0 ) {
     string input = w.substr(0,1) ;
     
     // State Epsilon
     if ( w.length() == 0 ) {
        if (lastV) {
           hNum[line]++ ;           
        }
        state = 3 ;   
     }
     
     // state awal
     if ( state == 0 ) {
        if ( isVowel(input) ) { return dfa(w.substr(1),1,1) ; } 
                                return dfa(w.substr(1),2) ;
     } else
     // State Vokal
     if ( state == 1 ) {
        if ( isVowel(input) ) { return dfa(w.substr(1),1,1) ; } // ketemu vokal, muter2
        if ( input == " " )   { hNum[line]++ ; return dfa(w.substr(1),0) ; }
        if ( input == "/" )   { hNum[line]++ ; return dfa(w.substr(1),3) ; }
        else {
             hNum[line]++ ;
             return dfa(w.substr(1),2) ; // kalau konsonan
        }
     } else 
     // State Konsonan
     if ( state == 2 ) {
        if ( isVowel(input) ) { return dfa(w.substr(1),1,1) ; }
        if ( input == " " )   { return dfa(w.substr(1),0) ; }
        if ( input == "/" )   { return dfa(w.substr(1),3) ; } 
        return dfa(w.substr(1),2) ; // kalau konsonan
     } else 
     // Final State
     if ( state == 3 ) {
        if ( line == 1 && hNum[line] != 5 ) { return "1" ;}
        if ( line == 1 && hNum[line] == 5 ) { line++ ; return dfa(w,0) ;}
        
        if ( line == 2 && hNum[line] != 7 ) { return "2" ;}
        if ( line == 2 && hNum[line] == 7 ) { line++ ; return dfa(w,0) ;}
        
        if ( line == 3 && hNum[line] != 5 ) { return "3" ;}
        if ( line == 3 && hNum[line] == 5 ) { return "Y" ;}
     }
}

int main() {
    char h[200] ;
    int flag = 1 ;
    
    cin.getline(h,200) ;
    
    if (!strcmp(h,"e/o/i")) { flag = 0 ; }
    
    while (flag)  {
       
       line = 1 ;
       hNum[1] = hNum[2] = hNum[3] = 0 ; 
         
       cout << dfa(h,0) << endl ;
       cin.getline(h,200) ;
    
       if (!strcmp(h,"e/o/i")) {
          flag = 0 ;                         
       }
    }
    
    //system("pause");
    return 0 ;
}

// nonDeterministic Finite Automata
/*
   state 0 :
     - kalau ketemu vokal ke state 1 
     - kalau ketemu konsonan ke state 2 ;
   state 1 :
     - kalau ketemu vokal tetep di state 1
     - kalau ketemu konsonan naik ke state 2 ; tambah l[line]
     - kalau ketemu spasi ke state 0 ; tambah l[line]
     - kalau ketemu garis miring ke state 3
   state 2 :
     - kalau ketemu vokal ke state 1 ;
     - kalau ketemu konsonan tetep di state 2 ;
     - kalau ketemu spasi ke stae 0 ;
     - kalau ketemu gatis miring ke state 3
   state 3 ;
      - tiap ganti baris, cek jumlah vowel sekarang
      - kalau != aturan, return char sesuai output
      - kalau udah di baris 3 dan sesuai aturan, return y
     
 */ 
