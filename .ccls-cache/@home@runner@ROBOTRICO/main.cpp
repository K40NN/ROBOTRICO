//#include "Plateau.h"
//#include "gtest/gtest.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/**
 * @brief Enumération représentant les différentes valeurs possibles pour une
 * case du jeu.
 */
enum class Valeur { Vide, Robot1, Robot2, Robot3, Robot4, Mur, Cible };

/**
 * @brief Structure représentant une case du jeu.
 */
struct Case {
  int positionX; /**< Coordonnée X de la case. */
  int positionY; /**< Coordonnée Y de la case. */
  Valeur valeur; /**< Valeur de la case. */
};

/**
 * @brief Classe représentant un joueur du jeu.
 */
class Joueur {
private:
  int numero;      /**< Numéro du joueur. */
  std::string nom; /**< Nom du joueur. */
  bool aJoue;      /**< Indicateur indiquant si le joueur a déjà joué. */
  int nombreCoup;  /**< Nombre de coups effectués par le joueur. */

public:
  /**
   * @brief Constructeur de la classe Joueur.
   * @param numero Le numéro du joueur.
   */
  Joueur(int numero) : numero(numero), aJoue(false), nombreCoup(0) {}

  /**
   * @brief Getter pour le numéro du joueur.
   * @return Le numéro du joueur.
   */
  int getNumero() const { return numero; }

  /**
   * @brief Getter pour le nom du joueur.
   * @return Le nom du joueur.
   */
  const std::string &getNom() const { return nom; }

  /**
   * @brief Setter pour le nom du joueur.
   * @param nouveauNom Le nouveau nom du joueur.
   */
  void setNom(const std::string &nouveauNom) { nom = nouveauNom; }

  /**
   * @brief Vérifie si le joueur a joué un coup.
   * @return True si le joueur a joué, False sinon.
   */
  bool aJoueCoup() const { return aJoue; }

  /**
   * @brief Setter pour l'indicateur de coup joué par le joueur.
   * @param aJoueCoup La valeur de l'indicateur de coup joué.
   */
  void setAJoueCoup(bool aJoueCoup) { aJoue = aJoueCoup; }

  /**
   * @brief Getter pour le nombre de coups effectués par le joueur.
   * @return Le nombre de coups effectués.
   */
  int getNombreCoup() const { return nombreCoup; }

  /**
   * @brief Setter pour le nombre de coups effectués par le joueur.
   * @param nouveauNombreCoup Le nouveau nombre de coups.
   */
  void setNombreCoup(int nouveauNombreCoup) { nombreCoup = nouveauNombreCoup; }

  /**
   * @brief Saisit le nom du joueur à partir de l'entrée standard.
   */
  void saisirNom() {
    std::cout << "Nom du joueur " << numero << ": ";
    std::cin >> nom;
  }

  /**
   * @brief Saisit le nombre de coups que le joueur compte faire à partir de
   * l'entrée standard.
   */
  void saisirNombreCoup() {
    std::cout << "Nombre de coups que le joueur " << numero
              << " compte faire : ";
    std::cin >> nombreCoup;
  }
};

// Fonction pour vérifier si la réponse de l'utilisateur est valide
template <typename T>
T getUserInput(const std::string &prompt,
               const std::initializer_list<T> &validChoices) {
  T userInput;
  bool isValidChoice = false;

  do {
    std::cout << prompt;
    std::cin >> userInput;

    for (const auto &choice : validChoices) {
      if (choice == userInput) {
        isValidChoice = true;
        break;
      }
    }

    if (!isValidChoice) {
      std::cout << "Réponse invalide. Veuillez réessayer." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (!isValidChoice);

  return userInput;
}

/**
 * @brief Génère une liste de joueurs à partir de l'entrée standard.
 * @return La liste de joueurs générée.
 */
std::vector<Joueur> genererListeJoueurs() {
  int nombreJoueurs;
  std::cout << "Nombre de joueurs : ";
  std::cin >> nombreJoueurs;

  // Création des joueurs
  std::vector<Joueur> joueurs;
  for (int i = 1; i <= nombreJoueurs; i++) {
    joueurs.emplace_back(i);
    joueurs.back().saisirNom();
    joueurs.back().saisirNombreCoup();
    joueurs.back().setAJoueCoup(false);
  }

  // Affichage des informations des joueurs
  std::cout << "Informations des joueurs :" << std::endl;
  for (const Joueur &joueur : joueurs) {
    std::cout << "Joueur " << joueur.getNumero() << ": " << joueur.getNom()
              << ", Nombre de coups : " << joueur.getNombreCoup() << std::endl;
  }

  return joueurs;
}

/**
 * @brief Obtient le joueur qui n'a pas encore joué et qui a le nombre de coups
 * minimum parmi les joueurs non joués.
 * @param joueurs La liste des joueurs.
 * @return Une référence vers le joueur non joué avec le nombre de coups
 * minimum.
 */
Joueur &obtenirJoueurNonJoueMinCoup(std::vector<Joueur> &joueurs) {
  Joueur *joueurMinCoupNonJoue = nullptr;

  for (Joueur &joueur : joueurs) {
    if (!joueur.aJoueCoup()) {
      if (joueurMinCoupNonJoue == nullptr ||
          joueur.getNombreCoup() < joueurMinCoupNonJoue->getNombreCoup()) {
        joueurMinCoupNonJoue = &joueur;
      }
    }
  }

  return *joueurMinCoupNonJoue;
}

/**
 * @brief Vérifie si tous les joueurs ont joué leurs coups.
 * @param joueurs La liste des joueurs.
 * @return True si tous les joueurs ont joué, False sinon.
 */

bool tousJoueursOntJoue(const std::vector<Joueur> &joueurs) {
  for (const Joueur &joueur : joueurs) {
    if (!joueur.aJoueCoup()) {
      return false;
    }
  }
  return true;
}

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
    repartirBarres();
    repartirAnglesMurs();
    //   repartirMursAleatoires();
    repartirRobots();
  }

  /**
   * @brief Effectue le lancement pour un joueur donné avec un nombre de coups
   * spécifié.
   *
   * @param joueurActuel Le numéro du joueur.
   * @param nombreCoupsJoueur Le nombre de coups que le joueur peut jouer.
   */
  void lancement_pour_joueur(int joueurActuel, int nombreCoupsJoueur) {
    while (nombreCoupsJoueur > 0) {
      // Affichage du plateau
      std::cout << "Nombre de coups qu'il reste à jouer : " << nombreCoupsJoueur
                << std::endl;

      std::cout << std::endl;
      // Déplacement des robots
      int numeroRobot = 0;

      numeroRobot =
          getUserInput<int>("Entrez le numéro du robot (1, 2, 3 ou 4) : ",
                            {1, 2, 3, 4}); // Vérification des choix possibles
      trouverEmplacementRobot(numeroRobot);
      char direction;

      direction = getUserInput<char>(
          "Entrez la direction de déplacement (haut : 'h', bas : 'b', gauche : "
          "'g', droite : 'd') : ",
          {'h', 'b', 'g', 'd'}); // Vérification des choix possibles
      deplacerRobot(numeroRobot, direction);
      // Vérification du nombre de coups restants
      afficherPlateau();
      nombreCoupsJoueur--;
      // Vérification si le joueur a atteint la cible
      if (verifierCibleAtteinte()) {
        std::cout << "Le joueur " << joueurActuel
                  << " a atteint la cible ! Fin de la partie." << std::endl;
        break;
      }
      if (nombreCoupsJoueur == 0) {
        std::cout << "Nombre de coups atteint pour le joueur " << joueurActuel
                  << ". Fin de la partie." << std::endl;
        break;
      }
    }
  }

  /**
   * @brief Affiche le plateau de jeu.
   */
  void afficherPlateau() {
    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
        if (cases[i][j].valeur == Valeur::Vide) {
          std::cout << " ";
        } else if (cases[i][j].valeur == Valeur::Robot1) {
          std::cout << "1";
        } else if (cases[i][j].valeur == Valeur::Robot2) {
          std::cout << "2";
        } else if (cases[i][j].valeur == Valeur::Robot3) {
          std::cout << "3";
        } else if (cases[i][j].valeur == Valeur::Robot4) {
          std::cout << "4";
        } else if (cases[i][j].valeur == Valeur::Mur) {
          std::cout << "@";
        } else if (cases[i][j].valeur == Valeur::Cible) {
          std::cout << "C";
        }

        std::cout << " ";
      }

      std::cout << std::endl;
    }
  }
  /**

  @brief Trouve l'emplacement actuel du robot sur le plateau.
  @param numeroRobot Le numéro du robot.
  */


/*TEST(trouverEmplacementRobot, RechercheRobot) {
EXPECT_EQ(, trouverEmplacementRobot(1));
}*/

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

  /**
   * @brief Déplace le robot spécifié dans une direction donnée.
   *
   * @param numeroRobot Le numéro du robot à déplacer.
   * @param direction La direction dans laquelle déplacer le robot ('h' pour
   * haut, 'b' pour bas, 'g' pour gauche, 'd' pour droite).
   */
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

  /**
   * @brief Vérifie si la cible a été atteinte.
   *
   * @return true si la cible a été atteinte, false sinon.
   */
  bool verifierCibleAtteinte() const {
    for (int i = 0; i < taille; i++) {
      for (int j = 0; j < taille; j++) {
        if (cases[i][j].valeur == Valeur::Cible) {
          return false;
        }
      }
    }
    return true;
  }

private:
  int voirplusoumoin() {
    // std::srand(std::time(0));
    return std::rand() % 2;
  }
  /**

  @brief Place les murs aux bordures du plateau.
  */
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
  /**

  @brief Place les barres horizontales et verticales sur le plateau.
  */
  void repartirBarres() {
    // Répartition des barres perpendiculaires aux bordures horizontales
    for (int i = 1; i < 4; i++) {
      // du haut
      cases[i][8].valeur = Valeur::Mur;
      cases[i][taille - 9].valeur = Valeur::Mur;
      // du bas
      cases[taille - i - 1][8].valeur = Valeur::Mur;
      cases[taille - i - 1][taille - 9].valeur = Valeur::Mur;
    }

    // Répartition des barres perpendiculaires aux bordures verticales
    for (int j = 1; j < 4; j++) {
      cases[8][j].valeur = Valeur::Mur;
      cases[taille - 9][j].valeur = Valeur::Mur;
      cases[8][taille - j - 1].valeur = Valeur::Mur;
      cases[taille - 9][taille - j - 1].valeur = Valeur::Mur;
    }
  }
  /**

  @brief Place les angles des murs sur le plateau.
  */
  void repartirAnglesMurs() {
    int anglesRestants = nbAngles;
    int cibleposee = 0;
    while (anglesRestants > 0) {
      // Génération d'un nombre aléatoire entre 0 et 1
      int X1 = -1;
      int X2 = -2;
      int X3 = -3;
      int Y1 = -1;
      int Y2 = -2;
      int Y3 = -3;
      int X = voirplusoumoin();
      int Y = voirplusoumoin();

      if (X == 0) {
        X1 = 1;
        X2 = 2;
        X3 = 3;
      } else {
        X1 = -1;
        X2 = -2;
        X3 = -3;
      }
      if (Y == 0) {
        Y1 = 1;
        Y2 = 2;
        Y3 = 3;
      } else {
        Y1 = -1;
        Y2 = -2;
        Y3 = -3;
      }

      int randomX = std::rand() % taille;
      int randomY = std::rand() % taille;

      if (cases[randomX][randomY].valeur == Valeur::Vide && randomX % 2 != 0 &&
          randomY % 2 != 0) {
        // Vérifier si les positions adjacentes sont également vides
        if (cases[randomX + X1][randomY].valeur == Valeur::Vide &&
            cases[randomX + X2][randomY].valeur == Valeur::Vide &&
            cases[randomX + X3][randomY].valeur == Valeur::Vide &&
            cases[randomX][randomY + Y1].valeur == Valeur::Vide &&
            cases[randomX][randomY + Y2].valeur == Valeur::Vide &&
            cases[randomX][randomY + Y3].valeur == Valeur::Vide &&

            cases[randomX + X1][randomY + Y1].valeur == Valeur::Vide &&
            cases[randomX + X1][randomY + Y2].valeur == Valeur::Vide &&
            cases[randomX + X1][randomY + Y3].valeur == Valeur::Vide &&
            cases[randomX + X1][randomY - Y1].valeur == Valeur::Vide &&

            cases[randomX + X2][randomY + Y1].valeur == Valeur::Vide &&
            cases[randomX + X3][randomY + Y1].valeur == Valeur::Vide &&
            cases[randomX - X1][randomY + Y1].valeur == Valeur::Vide &&

            cases[randomX][randomY - Y1].valeur == Valeur::Vide &&
            cases[randomX - X1][randomY].valeur == Valeur::Vide &&

            cases[randomX - X1][randomY - Y1].valeur == Valeur::Vide &&
            cases[randomX + X2][randomY - Y1].valeur == Valeur::Vide &&
            cases[randomX + X3][randomY - Y1].valeur == Valeur::Vide &&

            cases[randomX - X1][randomY + Y1].valeur == Valeur::Vide &&
            cases[randomX - X1][randomY + Y2].valeur == Valeur::Vide

        ) {
          // Placer les 5 murs de l'angle
          cases[randomX][randomY].valeur = Valeur::Mur;
          cases[randomX + X1][randomY].valeur = Valeur::Mur;
          cases[randomX + X2][randomY].valeur = Valeur::Mur;
          cases[randomX][randomY + Y1].valeur = Valeur::Mur;
          cases[randomX][randomY + Y2].valeur = Valeur::Mur;
          if (cibleposee == 0) {
            cases[randomX + X1][randomY + Y1].valeur = Valeur::Cible;
            cibleposee = 1;
          }

          anglesRestants--;
        }
      }
    }
  }
  /**

  @brief Place les robots sur le plateau de manière aléatoire.
  */
  void repartirRobots() {
    for (int k = 0; k < 4; k++) {
      int robotX, robotY;

      do {
        robotX = std::rand() % taille;
        robotY = std::rand() % taille;
      } while (cases[robotX][robotY].valeur == Valeur::Mur);

      if (k == 0) {
        cases[robotX][robotY].valeur = Valeur::Robot1;
      }
      if (k == 1) {
        cases[robotX][robotY].valeur = Valeur::Robot2;
      }
      if (k == 2) {
        cases[robotX][robotY].valeur = Valeur::Robot3;
      }
      if (k == 3) {
        cases[robotX][robotY].valeur = Valeur::Robot4;
      }
      // cases[robotX][robotY].valeur = static_cast<Valeur>(k + 2);
    }
  }
  /**
   * @brief Déplace le robot vers une nouvelle position en utilisant les deltas
   * spécifiés.
   *
   * @param x La coordonnée x actuelle du robot.
   * @param y La coordonnée y actuelle du robot.
   * @param deltaX Le delta à ajouter à la coordonnée x pour le déplacement.
   * @param deltaY Le delta à ajouter à la coordonnée y pour le déplacement.
   */
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

/**
 * @brief Lance une partie du jeu.
 */
void lancerUnePartie() {
  // Génération du plateau
  Plateau plateau;

  // Sauvegarde du plateau initial
  Plateau plateauInitial = plateau;

  // Affiche le plateau initial
  plateau.afficherPlateau();

  // Attente de 30 secondes
  std::cout << "Attente de 30 secondes..." << std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(30));

  // Génère la liste des joueurs
  std::vector<Joueur> listeJoueurs = genererListeJoueurs();

  // Boucle principale du jeu
  while (!tousJoueursOntJoue(listeJoueurs)) {
    // Réinitialise le plateau pour chaque joueur
    plateau = plateauInitial;
    plateau.afficherPlateau();
    // Obtient le prochain joueur qui n'a pas encore joué le moins de coups
    Joueur &joueurCourant = obtenirJoueurNonJoueMinCoup(listeJoueurs);
    joueurCourant.setAJoueCoup(true);

    // Affiche le joueur courant
    std::cout << "Lancement pour le joueur : " << joueurCourant.getNom()
              << std::endl;

    // Effectue le lancement pour le joueur courant
    plateau.lancement_pour_joueur(joueurCourant.getNumero(),
                                  joueurCourant.getNombreCoup());
  }

  // Proposer de rejouer une partie
  char choixRejouer;
  std::cout << "Rejouer une partie ? (O/N) : ";
  std::cin >> choixRejouer;

  if (choixRejouer == 'O' || choixRejouer == 'o') {
    lancerUnePartie();
  } else {
    cout << "End game ";
  }
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
  // Lance une partie du jeu
  lancerUnePartie();
}
