# Notes de continuité du projet

Ce fichier est destiné à conserver le contexte scientifique et technique du dépôt afin d'éviter toute perte d'information lors des prochaines étapes du projet.

## 1. Règle principale du projet

Ne pas supprimer l'ancien travail. Le superviseur a demandé de conserver les résultats historiques et d'ajouter les nouveaux résultats à la suite. Le `README.md` doit donc rester cumulatif : ancien rapport, résultats complémentaires, puis liens vers les fichiers d'interprétation.

## 2. Fichiers principaux

- `README.md` : rapport principal complet. Il contient l'ancien travail et les résultats ajoutés après les remarques du superviseur.
- `interpretation_physique_cinetique.md` : lecture synthétique des mécanismes physiques et cinétiques.
- `lecture_resultats_selon_references.md` : lecture figure par figure des résultats à la lumière des références scientifiques.
- `main.cpp` : version actuelle du code C++ utilisée pour régénérer les nouveaux résultats avec alpha = 0.
- `code_versions/main_original_before_alpha0.cpp` : version conservée avant l'ajout de alpha = 0.
- `code_versions/main_alpha0_full_xi_corrected.cpp` : version complète actuelle avec alpha = 0 et correction de P(xi) jusqu'à xi = 1.
- `figures/` : figures finales corrigées utilisées dans la partie complémentaire.
- `data/` : données post-traitées, notamment pour theta_max(alpha) et rho(xi)/rho_bulk.
- `PROJECT_INDEX.md` : index général du dépôt par sections scientifiques.
- `sections/section-I-modele-reference/` : copie organisée du modèle de référence, des figures historiques/corrigées et des versions principales du code.
- `sections/section-II-confinement/` : code, figures et interprétation de l'étude du rapport de confinement D/L_B.
- `sections/section-III-restitution/` : code, figures et interprétation de l'étude des coefficients de restitution.
- `references/README.md` : rôle scientifique des références utilisées dans l'interprétation.

## 3. Décisions scientifiques déjà prises

- La région proche de la surface est définie par xi <= 0.5.
- Le bulk est défini par xi > 0.5.
- La géométrie de référence utilise D = L_B.
- Les valeurs de alpha utilisées dans la version complète sont : 0, 0.5, 1, 2, 5, 10 et 100.
- Deux profils d'écoulement sont comparés : cisaillement linéaire uniforme et demi-profil parabolique de Poiseuille.
- Le cas alpha = 0 sert de référence brownienne : pas de rotation hydrodynamique imposée, mais diffusion brownienne et confinement géométrique conservés.

## 4. Interprétation physique à conserver

Les histogrammes ne représentent pas des trajectoires individuelles. Ils représentent des distributions stationnaires hors équilibre.

- P(theta) mesure le temps statistique passé par le bâtonnet dans chaque orientation.
- P(xi) mesure le temps statistique passé par le centre de masse à chaque distance réduite de la surface.
- theta_max est l'angle le plus probable, mais il doit être interprété avec prudence lorsque la distribution est large et peu contrastée.
- La couche de déplétion n'est pas une séparation de phase. Elle provient principalement de l'exclusion stérique imposée par la paroi et par la longueur finie du bâtonnet.
- Les oscillations visibles dans les distributions spatiales brutes P(xi) sont des oscillations statistiques de comptage. Elles ne doivent pas être interprétées comme des structures physiques périodiques.

## 5. Correction de P(xi) et binning

Le superviseur a demandé de compléter P(xi) jusqu'à xi = 1 et de diminuer les oscillations visibles dans les anciennes figures.

La correction a conduit à deux représentations complémentaires :

- figures brutes : `figures/Fig5a_raw_Pxi_linear.png` et `figures/Fig6a_raw_Pxi_parabolic.png` ;
- figures regroupées et normalisées : `figures/Fig5b_binned_Pxi_linear.png` et `figures/Fig6b_binned_Pxi_parabolic.png`.

Le binning avec Delta xi = 0.005 est un post-traitement statistique. Il ne modifie pas la dynamique brownienne, le cisaillement, les collisions avec la paroi ni la géométrie du modèle.

## 6. Références utilisées dans l'interprétation

- Balakrishnan : cadre général de physique statistique hors équilibre, Langevin, Fokker-Planck, bruit brownien et état stationnaire.
- Boeder, Khater, Tannous et Hijazi : distributions angulaires P(theta), orientation de macromolécules allongées sous écoulement laminaire et rôle de alpha comme nombre de Péclet rotationnel.
- Hijazi 2000 : référence historique très proche du projet, centrée sur les densités de probabilité de macromolécules sous écoulement laminaire.
- Atwi 2012, 2013, 2016 : mésopores, bulk, couche de déplétion, Poiseuille, collisions avec les parois, restitution et interactions de surface.

## 7. Points à ne pas faire sans accord explicite

- Ne pas supprimer les anciennes figures historiques Fig1.png à Fig20.png.
- Ne pas remplacer les figures brutes par les figures binnées : les deux sont utiles car elles montrent la correction statistique.
- Ne pas supprimer les versions conservées du code dans `code_versions/`.
- Ne pas transformer la couche de déplétion en interprétation de séparation de phase.
- Ne pas attribuer directement au livre de Balakrishnan les équations spécifiques du bâtonnet ; Balakrishnan donne le cadre stochastique général, tandis que les équations de rotation des macromolécules viennent plutôt de Boeder, Hijazi, Khater, Tannous et Atwi.

## 8. Prochaines extensions scientifiques prévues

Les prochaines tâches discutées avec le superviseur concernent deux directions nouvelles :

1. Étude de l'effet du diamètre du mésopore D, en particulier lorsque D devient inférieur ou comparable à la longueur du bâtonnet L_B.
2. Étude de l'effet des coefficients de restitution e et e' sur les distributions P(theta) et P(xi).

Ces deux extensions doivent être traitées comme de nouvelles simulations, pas comme un simple changement de présentation Origin.

## 9. Remarque sur le dépôt public

Le dépôt contient actuellement un fichier PDF du livre de Balakrishnan. Pour un dépôt public, il peut être préférable de conserver uniquement la référence bibliographique et le DOI, sauf si le partage du PDF est explicitement autorisé. Ne pas supprimer ce fichier sans accord explicite de Hussein.

## 10. État actuel

Dernière organisation confirmée : le dépôt conserve l'ancien travail, ajoute les résultats corrigés avec alpha = 0, ajoute les figures P(xi) brutes et binnées, ajoute les courbes theta_max(alpha), et contient deux fichiers d'interprétation scientifique complémentaires.

## 11. Organisation actuelle par sections

Le dépôt est maintenant structuré comme un cahier de recherche :

1. Section I : modèle de référence et résultats historiques conservés.
2. Section II : effet du confinement D/L_B.
3. Section III : effet des coefficients de restitution.

Cette organisation n'annule pas l'ancien README cumulatif. Elle ajoute des dossiers lisibles pour retrouver rapidement les codes, figures et interprétations associés à chaque tâche scientifique.
