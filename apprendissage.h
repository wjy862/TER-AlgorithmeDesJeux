
double CalculerUtilite(Sommet pSommet){
    double benefice=pSommet->benefice;
    double maxBenefice=pSommet->maxBenefice;
    double minBenefice=pSommet->minBenefice;
    return 1.0-((maxBenefice-benefice)/(maxBenefice-minBenefice));
}
