# Index scientifique du dépôt

Ce dépôt est organisé comme un cahier de recherche numérique. Les anciens résultats sont conservés, et les extensions demandées par le superviseur sont ajoutées sous forme de sections séparées.

## Structure générale

- [Section I - Modèle de référence](sections/section-I-modele-reference/README.md)  
  Simulation de référence avec \(D=L_B\), comparaison entre cisaillement linéaire et demi-profil parabolique, distributions \(P(\theta)\), \(P(\xi)\), séparation volume/couche de déplétion et courbes \(\theta_{\max}(\alpha)\).

- [Section II - Effet du confinement](sections/section-II-confinement/README.md)  
  Étude du rapport géométrique \(D/L_B\), en particulier lorsque le diamètre du mésopore devient comparable ou inférieur à la longueur du bâtonnet.

- [Section III - Effet de la restitution](sections/section-III-restitution/README.md)  
  Étude de l'influence des coefficients de restitution aux parois sur les distributions angulaires et spatiales.

- [Références scientifiques](references/README.md)  
  Rôle des références de Balakrishnan, Hijazi, Khater, Tannous et Atwi dans l'interprétation physique du modèle.

- [Méthodologie et validation](METHODOLOGIE_VALIDATION.md)
  Distinction entre résultats directement simulés, grandeurs dérivées par post-traitement et relations analytiques utilisées comme repères physiques.

## Principe de conservation

Les figures historiques situées à la racine du dépôt ne sont pas supprimées. Les dossiers de sections contiennent des copies organisées des codes et figures nécessaires à la lecture scientifique.

## Données numériques

Les fichiers bruts `.txt` issus des simulations ne sont pas versionnés systématiquement dans le dépôt public. Les résultats conservés sont les codes C++, les figures finales et les documents d'interprétation. Les fichiers `.txt` peuvent être régénérés localement à partir des codes placés dans chaque section.

## Résultats calculés et résultats dérivés

Les histogrammes \(P(\theta)\) et \(P(\xi)\) proviennent des simulations numériques.

Les grandeurs comme \(\theta_{\max}\), la fraction de surface ou les distributions regroupées par binning sont des quantités dérivées par post-traitement statistique.

La courbe de l'angle limite géométrique en Section II est une relation analytique de confinement, utilisée comme repère physique pour interpréter les distributions simulées.

Les interprétations détaillées des nouvelles extensions sont disponibles ici :

- [Interprétation détaillée de la Section II](sections/section-II-confinement/INTERPRETATION_DETAILLEE.md)
- [Interprétation détaillée de la Section III](sections/section-III-restitution/INTERPRETATION_DETAILLEE.md)
