# Interprétation détaillée - Section II : effet du confinement géométrique

Cette section analyse l'effet du rapport \(D/L_B\) sur la dynamique d'un bâtonnet brownien soumis à un écoulement. Elle prolonge le modèle de référence en considérant des pores dont le diamètre peut devenir inférieur à la longueur du bâtonnet.

## 1. Idée physique centrale

Lorsque \(D=L_B\), le bâtonnet dispose encore d'un espace angulaire relativement large. Lorsque \(D/L_B\) diminue, certaines orientations deviennent géométriquement interdites, car les extrémités du bâtonnet rencontreraient les parois.

La contrainte de non-intersection avec les parois s'écrit :

\[
L_B |\sin\theta| \leq D.
\]

Elle conduit à :

\[
\theta_{\mathrm{limite}}=\arcsin\left(\frac{D}{L_B}\right)
\]

pour \(D<L_B\). Cette relation n'est pas extraite de l'histogramme : elle sert de repère géométrique pour interpréter les résultats numériques.

## 2. Pourquoi utiliser \(\alpha=100\) ?

Le choix \(\alpha=100\) place le système dans un régime où l'entraînement hydrodynamique est fort par rapport à la diffusion rotationnelle brownienne. Cela permet de voir plus clairement si l'orientation finale est imposée par l'écoulement, par la géométrie du pore, ou par les deux.

À faible \(\alpha\), le bruit brownien masquerait plus facilement l'effet géométrique. À fort \(\alpha\), la compétition entre alignement hydrodynamique et confinement stérique devient plus lisible.

## 3. Lecture des figures

### Figure II-1

La Figure II-1 représente l'angle limite géométrique en fonction de \(D/L_B\). Elle montre que la réduction du diamètre du pore réduit rapidement le domaine angulaire accessible. Pour \(D/L_B=1\), l'angle limite vaut \(90^\circ\). Pour \(D/L_B=0.5\), il tombe à environ \(30^\circ\), et pour \(D/L_B=0.25\), il devient proche de \(14.5^\circ\).

Cette figure constitue donc une référence géométrique : elle indique ce que la paroi autorise avant même de considérer le cisaillement ou la diffusion brownienne.

### Figures II-2 à II-4

Les Figures II-2, II-3 et II-4 montrent l'évolution de \(\theta_{\max}\) dans différentes régions du pore. La comparaison entre ces figures permet de séparer l'effet du volume, de la surface et du centre.

Dans le volume, \(\theta_{\max}\) reflète surtout la compétition entre cisaillement et espace angulaire accessible. Près de la surface, la paroi impose une orientation plus parallèle à la surface, ce qui rend l'interprétation de \(\theta_{\max}\) plus fortement géométrique. Dans la région centrale, l'effet direct des collisions avec la paroi est plus faible, mais le confinement global reste visible lorsque \(D/L_B\) diminue.

### Figure II-5

La Figure II-5 donne la fraction statistique de présence près de la surface. Elle indique comment la réduction de \(D/L_B\) redistribue le temps passé par le bâtonnet entre les régions accessibles du pore.

Lorsque le confinement devient plus fort, la distinction entre volume et couche proche de la surface devient plus délicate, car une grande partie de l'espace disponible se trouve influencée par les parois.

### Figures II-6 et II-7

Les Figures II-6 et II-7 présentent \(P(\theta)\) dans le volume, respectivement pour le cisaillement linéaire et pour l'écoulement de Poiseuille.

Le resserrement de \(D/L_B\) réduit l'étendue angulaire accessible et modifie la forme des distributions. Dans le cas linéaire, le taux de cisaillement est spatialement uniforme. Dans le cas de Poiseuille, le cisaillement local dépend de la position transverse, ce qui introduit une superposition de régimes locaux.

### Figures II-8 et II-9

Les Figures II-8 et II-9 montrent \(P(\theta)\) près de la surface. Dans cette région, l'effet de la paroi est dominant : les orientations fortement inclinées sont défavorisées parce qu'elles augmentent la probabilité de contact avec la surface.

Le pic de \(P(\theta)\) près de la surface doit donc être interprété comme le résultat d'une sélection stérique et dynamique : le bâtonnet reste plus facilement dans des orientations compatibles avec le glissement le long de la paroi.

### Figures II-10 et II-11

Les Figures II-10 et II-11 représentent \(P(\xi)\). Elles montrent comment la position transverse est modifiée par le confinement.

Ces distributions sont particulièrement sensibles à la géométrie, car \(\xi\) mesure directement la position du centre de masse dans le pore. Les structures fines ou pics locaux doivent être lus en tenant compte du binning, du nombre fini d'itérations et de la réduction de l'espace accessible lorsque \(D/L_B\) diminue.

## 4. Conclusion physique

La Section II montre que le confinement n'agit pas seulement comme une limite spatiale. Il transforme aussi la statistique orientationnelle. Lorsque \(D/L_B\) diminue, les parois sélectionnent les orientations compatibles avec la géométrie du mésopore.

Cette lecture est cohérente avec les travaux sur les macromolécules sous écoulement laminaire et avec l'interprétation des mésopores comme systèmes où les surfaces modifient simultanément la distribution spatiale \(P(\xi)\) et la distribution angulaire \(P(\theta)\).
