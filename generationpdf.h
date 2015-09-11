#ifndef GENERATIONPDF_H
#define GENERATIONPDF_H

class generationpdf
{

    public:

        generationpdf();
        ecrireTexte();
        chargerImage();
        fermer();

    private:
        PDF::PDF(){};
};

#endif // GENERATIONPDF_H
