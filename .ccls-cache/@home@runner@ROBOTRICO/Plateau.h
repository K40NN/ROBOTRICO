#ifndef PLATEAU_H
#define PLATEAU_H

#include <cstdlib>
#include <ctime>
#include <iostream>

enum class Valeur { Vide, Robot1, Robot2, Robot3, Robot4, Mur, Cible };

struct Case {
  int positionX;
  int positionY;
  Valeur valeur;
};

class Plateau {

public:

  // Constructeur 
  Plateau();

/*
  // Accesseur pour l'attribut privé 'cases'
  const Case& getCase(int x, int y) const;
  // Accesseur pour l'attribut privé 'taille'
  int getTaille() const;
  // Accesseur pour l'attribut privé 'tailleCarre'
  static int getTailleCarre();
  // Accesseur pour l'attribut privé 'nbAngles'
  static int getNbAngles();
*/

  void afficherPlateau();
  void trouverEmplacementRobot(int numeroRobot);
  bool deplacerRobot(int numeroRobot, char direction);
  bool verifierCibleAtteinte() ;

private:
  static const int taille = 33;
  static const int tailleCarre = 8;
  static const int nbAngles = 15;
  Case cases[taille][taille];

  void placerCibleAleatoirement();
  int voirplusoumoin();
  void repartirAnglesMurs();
  void repartirMursBordures();
  void repartirRobots();
  bool deplacerRobotVers(int x, int y, int deltaX, int deltaY);
};

#endif // PLATEAU_H
