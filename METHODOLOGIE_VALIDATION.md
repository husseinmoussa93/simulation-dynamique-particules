# Méthodologie, validation et lecture scientifique des résultats

Ce document précise comment lire les résultats du dépôt. Il distingue les observables directement accumulées par la simulation, les grandeurs obtenues par post-traitement et les relations analytiques utilisées comme repères physiques.

## 1. Nature du modèle numérique

Le modèle décrit un bâtonnet brownien rigide confiné dans un mésopore et soumis à un écoulement de cisaillement. La dynamique résulte de trois contributions principales :

- une rotation brownienne aléatoire, associée aux fluctuations thermiques ;
- une rotation hydrodynamique déterministe, associée au cisaillement local ;
- une contrainte géométrique imposée par les parois du pore.

Cette lecture correspond au cadre général de la physique statistique hors équilibre : un forçage externe maintient le système dans un état stationnaire statistique, tandis que les fluctuations browniennes empêchent une trajectoire strictement déterministe.

## 2. Observables directement simulées

Les grandeurs suivantes sont obtenues par accumulation statistique dans le code C++ :

- les histogrammes angulaires \(P(\theta)\) ;
- les histogrammes spatiaux \(P(\xi)\) ;
- les histogrammes conditionnels dans le volume et près de la surface ;
- la fraction statistique de présence près de la surface ;
- les comparaisons entre cisaillement linéaire et écoulement de Poiseuille.

Les distributions ne doivent pas être lues comme une trajectoire individuelle. Elles décrivent le temps statistique passé par le bâtonnet dans certaines orientations ou certaines positions.

## 3. Grandeurs dérivées par post-traitement

La quantité \(\theta_{\max}\) est extraite comme le centre de la classe angulaire où \(P(\theta)\) atteint sa valeur maximale. Elle représente donc un maximum numérique de l'histogramme, et non une loi analytique imposée.

Cette grandeur est physiquement pertinente lorsque la distribution présente un pic net. Lorsque \(P(\theta)\) est presque plate ou fortement bruitée, notamment à faible \(\alpha\), le maximum numérique doit être interprété avec prudence : il peut correspondre à une fluctuation statistique plutôt qu'à une orientation préférentielle réelle.

Les courbes \(P(\xi)\) regroupées par binning utilisent une moyenne locale sur une largeur \(\Delta\xi=0.005\). Ce traitement réduit les oscillations rapides des histogrammes bruts sans modifier la structure globale de la distribution.

## 4. Relation analytique de confinement

Dans la Section II, l'angle limite géométrique n'est pas un résultat de simulation. Il s'agit d'un repère analytique obtenu à partir de la condition stérique :

\[
L_B |\sin\theta| \leq D.
\]

Lorsque \(D<L_B\), cette condition donne :

\[
\theta_{\mathrm{limite}}=\arcsin\left(\frac{D}{L_B}\right).
\]

Lorsque \(D\geq L_B\), l'ensemble des orientations géométriques reste accessible et l'angle limite devient \(90^\circ\).

Cette relation permet de comprendre pourquoi la réduction de \(D/L_B\) resserre fortement l'espace angulaire accessible.

## 5. Organisation scientifique des sections

La Section I constitue le modèle de référence avec \(D=L_B\). Elle étudie l'effet de \(\alpha\), c'est-à-dire le rapport entre l'entraînement hydrodynamique et la diffusion rotationnelle brownienne.

La Section II isole l'effet du confinement géométrique en faisant varier \(D/L_B\). Le choix \(\alpha=100\) rend l'alignement hydrodynamique suffisamment fort pour faire apparaître clairement la compétition avec la contrainte stérique.

La Section III étudie les coefficients de restitution aux parois. Ceux-ci représentent une condition de bord effective : ils contrôlent la manière dont le bâtonnet conserve ou perd une partie de sa dynamique après interaction avec la surface.

## 6. Lien avec les références

Balakrishnan fournit le cadre général des processus stochastiques hors équilibre : fluctuations browniennes, dissipation, forçage externe et état stationnaire statistique.

Les travaux de Hijazi, Khater, Tannous et Boeder justifient l'étude de distributions de probabilité de macromolécules sous écoulement laminaire, en particulier les distributions \(P(\theta)\) et \(P(\xi)\).

La thèse de Hijazi soutient directement la construction de densités de probabilité plutôt que l'analyse d'une seule trajectoire.

Les travaux d'Atwi sont reliés au rôle du mésopore, des surfaces et de la couche de déplétion dans la sélection spatiale et angulaire.

## 7. Limites actuelles

Les résultats publiés correspondent à des simulations numériques reproductibles avec graines fixes. Cette stratégie facilite les comparaisons entre paramètres, mais ne remplace pas une étude complète d'incertitude statistique.

Aucune barre d'erreur indépendante n'est encore calculée. Les conclusions qualitatives sont donc plus robustes que les valeurs ponctuelles de maxima dans les régimes faiblement contrastés.

Les coefficients de restitution utilisés dans la Section III doivent être lus comme des paramètres phénoménologiques de condition de bord. Leur calibration expérimentale nécessiterait un travail supplémentaire.
