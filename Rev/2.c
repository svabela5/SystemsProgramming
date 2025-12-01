union id { 
   char id[10]; 
   char passport[15]; 
}; 

struct person { 
   union id identification;
   char email[50]; 
   char title[50]; 
}; 