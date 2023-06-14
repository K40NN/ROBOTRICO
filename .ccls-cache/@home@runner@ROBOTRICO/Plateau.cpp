
#include "Plateau.h"


// Constructeur
Plateau() {
  // Génération aléatoire
  std::srand(std::time(0));  

  // Initialisation de toutes les cases du plateau
  for (int i = 0; i < Plateau::taille; i++) {
    for (int j = 0; j < Plateau::taille; j++) {
      Plateau::cases[i][j].positionX = i;
      Plateau::cases[i][j].positionY = j;

      // Les cases du carré central sont des murs, les autres sont vides
      if (i >= (Plateau::taille - Plateau::tailleCarre) / 2 &&
          i < (Plateau::taille - Plateau::tailleCarre) / 2 + Plateau::tailleCarre &&
          j >= (Plateau::taille - Plateau::tailleCarre) / 2 &&
          j < (Plateau::taille - Plateau::tailleCarre) / 2 + Plateau::tailleCarre) {
        Plateau::cases[i][j].valeur = Valeur::Mur;
      } else {
        Plateau::cases[i][j].valeur = Valeur::Vide;
      }
    }
  }

  repartirMursBordures();
  repartirAnglesMurs();
  // Il serait préférable de placer la cible en même temps que le premier angle
  placerCibleAleatoirement();
  // repartirMursAleatoires();
  repartirRobots();
}

bool verifierCibleAtteinte()  {
  for (const Case &casePlateau : cases) {
    if (casePlateau.valeur == Valeur::Cible) {
      return false; // La cible existe toujours dans le plateau
    }
  }
  return true; // La cible n'existe plus dans le plateau
}


// Affiche le plateau
void static afficherPlateau() {
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < Plateau::taille; j++) {
      if (cases[i][j].valeur == Valeur::Vide) {
        std::cout << " ";
      } else if (Plateau::cases[i][j].valeur == Valeur::Robot1) {
        std::cout << "1";
      } else if (Plateau::cases[i][j].valeur == Valeur::Robot2) {
        std::cout << "2";
      } else if (Plateau::cases[i][j].valeur == Valeur::Robot3) {
        std::cout << "3";
      } else if (Plateau::cases[i][j].valeur == Valeur::Robot4) {
        std::cout << "4";
      } else if (Plateau::cases[i][j].valeur == Valeur::Mur) {
        std::cout << "@";
      } else if (Plateau::cases[i][j].valeur == Valeur::Cible) {
        std::cout << "C";
      }

      std::cout << " ";
    }

    std::cout << std::endl;
  }
}

// Trouve l'emplacement d'un robot en fonction de son numéro
void trouverEmplacementRobot(int numeroRobot) {
  for (int i = 0; i < Plateau::taille; i++) {
    for (int j = 0; j < Plateau::taille; j++) {
      switch (cases[i][j].valeur) {
      case Valeur::Robot1:
        if (numeroRobot == 1) {
          std::cout << "Emplacement du robot 1 : (" << i << ", " << j << ")"
                    << std::endl;
          return;
        }
        break;
      case Valeur::Robot2:
        if (numeroRobot == 2) {
          std::cout << "Emplacement du robot 2 : (" << i << ", " << j << ")"
                    << std::endl;
          return;
        }
        break;
      case Valeur::Robot3:
        if (numeroRobot == 3) {
          std::cout << "Emplacement du robot 3 : (" << i << ", " << j << ")"
                    << std::endl;
          return;
        }
        break;
      case Valeur::Robot4:
        if (numeroRobot == 4) {
          std::cout << "Emplacement du robot 4 : (" << i << ", " << j << ")"
                    << std::endl;
          return;
        }
        break;
      }
    }
  }

  std::cout << "Robot non trouvé !" << std::endl;
}

// Déplace le robot aux coordonnées (x, y) vers la direction spécifiée par
// (deltaX, deltaY)
bool deplacerRobotVers(int x, int y, int deltaX, int deltaY) {
  int newX = x + deltaX;
  int newY = y + deltaY;

  // Vérifier si les nouvelles coordonnées sont valides
  if (newX < 0 || newX >= taille || newY < 0 || newY >= taille ||
      cases[newX][newY].valeur == Valeur::Mur) {
    std::cout << "Déplacement impossible !" << std::endl;
    return false;
  }

  // Vérifier si la case de destination est occupée par un autre robot
  if (cases[newX][newY].valeur != Valeur::Vide) {
    std::cout << "Déplacement impossible : case occupée !" << std::endl;
    return false;
  }

  // Déplacer le robot
  cases[newX][newY].valeur = cases[x][y].valeur;
  cases[x][y].valeur = Valeur::Vide;
  return true;
}

// Déplace un robot dans une direction donnée
bool deplacerRobot(int numeroRobot, char direction) {
  int deltaX = 0;
  int deltaY = 0;

  switch (direction) {
  case 'h':
    deltaX = -1;
    break;
  case 'b':
    deltaX = 1;
    break;
  case 'g':
    deltaY = -1;
    break;
  case 'd':
    deltaY = 1;
    break;
  default:
    std::cout << "Direction invalide !" << std::endl;
    return false; // Ajout d'un retour de booléen en cas d'erreur
  }

  bool success = false;
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      switch (cases[i][j].valeur) {
      case Valeur::Robot1:
        if (numeroRobot == 1) {
          success = deplacerRobotVers(i, j, deltaX, deltaY);
          return success;
        }
        break;
      case Valeur::Robot2:
        if (numeroRobot == 2) {
          success = deplacerRobotVers(i, j, deltaX, deltaY);
          return success;
        }
        break;
      case Valeur::Robot3:
        if (numeroRobot == 3) {
          success = deplacerRobotVers(i, j, deltaX, deltaY);
          return success;
        }
        break;
      case Valeur::Robot4:
        if (numeroRobot == 4) {
          success = deplacerRobotVers(i, j, deltaX, deltaY);
          return success;
        }
        break;
      }
    }
  }
  std::cout << "Robot non trouvé !" << std::endl;
  return false; // Ajout d'un retour de booléen en cas d'erreur
}
 
// Place la cible aléatoirement sur le plateau
void placerCibleAleatoirement() {
  int cibleX, cibleY;

  do {
    cibleX = std::rand() % taille;
    cibleY = std::rand() % taille;
  } while (cases[cibleX][cibleY].valeur != Valeur::Vide);

  cases[cibleX][cibleY].valeur = Valeur::Cible;
}

// Retourne aléatoirement 0 ou 1
int voirplusoumoin() {
  // std::srand(std::time(0));
  return std::rand() % 2;
}

// Répartit les angles des murs sur le plateau
void repartirAnglesMurs() {
  int anglesRestants = nbAngles;

  while (anglesRestants > 0) {
    int X1 = -1;
    int X2 = -2;
    int Y1 = -1;
    int Y2 = -2;
    int X = voirplusoumoin();
    int Y = voirplusoumoin();
    if (X == 0) {
      X1 = 1;
      X2 = 2;
    } else {
      X1 = -1;
      X2 = -2;
    }
    if (Y == 0) {
      Y1 = 1;
      Y2 = 2;
    } else {
      Y1 = -1;
      Y2 = -2;
    }

    int randomX = std::rand() % taille;
    int randomY = std::rand() % taille;

    if (cases[randomX][randomY].valeur == Valeur::Vide && randomX % 2 != 0 &&
        randomY % 2 != 0) {
      // Vérifier si les positions adjacentes sont également vides
      if (cases[randomX + X1][randomY].valeur == Valeur::Vide &&
          cases[randomX + X2][randomY].valeur == Valeur::Vide &&
          cases[randomX][randomY + Y1].valeur == Valeur::Vide &&
          cases[randomX][randomY + Y2].valeur == Valeur::Vide) {
        // Placer les 5 murs de l'angle
        cases[randomX][randomY].valeur = Valeur::Mur;
        cases[randomX + X1][randomY].valeur = Valeur::Mur;
        cases[randomX + X2][randomY].valeur = Valeur::Mur;
        cases[randomX][randomY + Y1].valeur = Valeur::Mur;
        cases[randomX][randomY + Y2].valeur = Valeur::Mur;

        anglesRestants--;
      }
    }
  }
}

// Répartit les murs sur les bordures du plateau
void repartirMursBordures() {
  // Répartition des murs sur les bordures horizontales
  for (int i = 0; i < taille; i++) {
    cases[i][0].valeur = Valeur::Mur;
    cases[i][taille - 1].valeur = Valeur::Mur;
  }

  // Répartition des murs sur les bordures verticales
  for (int j = 1; j < taille - 1; j++) {
    cases[0][j].valeur = Valeur::Mur;
    cases[taille - 1][j].valeur = Valeur::Mur;
  }
}

// Répartit les robots sur le plateau
void repartirRobots() {
  for (int k = 0; k < 4; k++) {
    int robotX, robotY;

    do {
      robotX = std::rand() % taille;
      robotY = std::rand() % taille;
    } while (cases[robotX][robotY].valeur == Valeur::Mur);

    cases[robotX][robotY].valeur = static_cast<Valeur>(k + 2);
  }
}
