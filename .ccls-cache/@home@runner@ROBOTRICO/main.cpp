#include <cstdlib>
#include <ctime>
#include <iostream>

enum class Valeur { Vide, Mur, Robot1, Robot2, Robot3, Robot4 };

struct Case {
  int positionX;
  int positionY;
  Valeur valeur;
};

class Plateau {
public:
  static const int taille = 33;
  static const int tailleCarre = 8;
  static const int nbAngles = 15;

  Case cases[taille][taille];

  Plateau() {
    std::srand(std::time(0));

    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
        cases[i][j].positionX = i;
        cases[i][j].positionY = j;

        if (i >= (taille - tailleCarre) / 2 &&
            i < (taille - tailleCarre) / 2 + tailleCarre &&
            j >= (taille - tailleCarre) / 2 &&
            j < (taille - tailleCarre) / 2 + tailleCarre) {
          cases[i][j].valeur = Valeur::Mur;
        } else {
          cases[i][j].valeur = Valeur::Vide;
        }
      }
    }
    repartirMursBordures();
    repartirAnglesMurs();
    // repartirMursAleatoires();
    repartirRobots();
  }

  void afficherPlateau() {
    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
        switch (cases[i][j].valeur) {
        case Valeur::Vide:
          std::cout << " ";
          break;
        case Valeur::Mur:
          std::cout << "@";
          break;
        case Valeur::Robot1:
          std::cout << "1";
          break;
        case Valeur::Robot2:
          std::cout << "2";
          break;
        case Valeur::Robot3:
          std::cout << "3";
          break;
        case Valeur::Robot4:
          std::cout << "4";
          break;
        }
      }
      std::cout << std::endl;
    }
  }

  void trouverEmplacementRobot(int numeroRobot) {
    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
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

  void deplacerRobot(int numeroRobot, char direction) {
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
      return;
    }

    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
        switch (cases[i][j].valeur) {
        case Valeur::Robot1:
          if (numeroRobot == 1) {
            deplacerRobotVers(i, j, deltaX, deltaY);
            return;
          }
          break;
        case Valeur::Robot2:
          if (numeroRobot == 2) {
            deplacerRobotVers(i, j, deltaX, deltaY);
            return;
          }
          break;
        case Valeur::Robot3:
          if (numeroRobot == 3) {
            deplacerRobotVers(i, j, deltaX, deltaY);
            return;
          }
          break;
        case Valeur::Robot4:
          if (numeroRobot == 4) {
            deplacerRobotVers(i, j, deltaX, deltaY);
            return;
          }
          break;
        }
      }
    }

    std::cout << "Robot non trouvé !" << std::endl;
  }

private:
  int voirplusoumoin() {
    // std::srand(std::time(0));
    return std::rand() % 2;
  }
  void repartirAnglesMurs() {
    int anglesRestants = nbAngles;

    while (anglesRestants > 0) {
      // Génération d'un nombre aléatoire entre 0 et 1
      // std::srand(std::time(0));
      // int X = std::rand() % 2;
      // int Y = std::rand() % 2;
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

  void deplacerRobotVers(int x, int y, int deltaX, int deltaY) {
    int newX = x + deltaX;
    int newY = y + deltaY;

    while (newX >= 0 && newX < taille && newY >= 0 && newY < taille &&
           cases[newX][newY].valeur != Valeur::Mur) {
      // Déplacer le robot
      cases[newX][newY].valeur = cases[x][y].valeur;
      cases[x][y].valeur = Valeur::Vide;

      x = newX;
      y = newY;
      newX += deltaX;
      newY += deltaY;
    }
  }
};

int main() {
  Plateau plateau;
  plateau.afficherPlateau();

  char continuer = 'o';

  while (continuer == 'o') {
    int numeroRobot;
    std::cout << "Entrez le numéro du robot (1, 2, 3 ou 4) : ";
    std::cin >> numeroRobot;

    plateau.trouverEmplacementRobot(numeroRobot);

    char direction;
    std::cout << "Entrez la direction de déplacement (haut : 'h', bas : 'b', "
                 "gauche : 'g', droite : 'd') : ";
    std::cin >> direction;

    plateau.deplacerRobot(numeroRobot, direction);

    std::cout << "Plateau après déplacement :" << std::endl;
    plateau.afficherPlateau();

    std::cout << "Voulez-vous déplacer un autre robot ? (o/n) : ";
    std::cin >> continuer;
  }

  return 0;
}
