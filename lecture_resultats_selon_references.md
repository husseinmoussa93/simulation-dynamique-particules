# Lecture des résultats à la lumière des références

Ce document relie explicitement les figures du dépôt aux références théoriques utilisées dans le projet. Il ne remplace pas le rapport principal ; il sert de couche d'interprétation physique et cinétique, afin que chaque résultat numérique soit compris dans un cadre scientifique clair.

Les références jouent trois rôles complémentaires :

- Balakrishnan fournit le cadre de la physique statistique hors équilibre : diffusion, bruit brownien, description de Langevin, formulation de Fokker-Planck et état stationnaire.
- Boeder, Khater, Tannous et Hijazi fournissent le cadre des distributions angulaires $P(\theta)$ pour des macromolécules allongées en écoulement laminaire, ainsi que l'interprétation de $\alpha$ comme nombre de Péclet rotationnel.
- Atwi fournit le cadre des particules anisotropes confinées dans des mésopores : distinction entre bulk et couche de déplétion, effet de la paroi, écoulement de Poiseuille, collisions diffusives, restitution et interactions de surface.

## 1. Principe général de lecture des figures

Toutes les figures doivent être lues comme des distributions statistiques stationnaires, et non comme des trajectoires individuelles. Le bâtonnet subit en permanence une compétition entre :

$$
\text{diffusion brownienne rotationnelle}
\quad \leftrightarrow \quad
\text{cisaillement hydrodynamique}
\quad \leftrightarrow \quad
\text{confinement stérique}.
$$

La diffusion brownienne rotationnelle tend à élargir les distributions angulaires. Le cisaillement hydrodynamique tend à sélectionner certaines orientations. La paroi réduit l'espace géométrique accessible, surtout dans la couche de déplétion.

Cette lecture est cohérente avec la description hors équilibre de Balakrishnan : le système peut atteindre une distribution stationnaire sans être à l'équilibre thermodynamique, car le cisaillement maintient une sollicitation extérieure permanente.

## 2. Figures angulaires sous cisaillement linéaire

### Figures historiques Fig1-Fig4

Les figures historiques `Fig1.png` à `Fig4.png` montrent l'évolution de $P(\theta)$ sous cisaillement linéaire, dans le bulk et près de la surface, pour plusieurs valeurs de $\alpha$.

Dans le bulk, l'interprétation suit directement l'approche de Boeder et des travaux de Hijazi, Khater et Tannous : $P(\theta)$ traduit le temps statistique passé par le bâtonnet dans chaque intervalle angulaire. Lorsque $\alpha$ est faible, la diffusion brownienne rotationnelle reste dominante et la distribution est large. Lorsque $\alpha$ augmente, le cisaillement hydrodynamique devient plus efficace et la distribution se concentre progressivement autour d'un angle préférentiel.

Près de la surface, la lecture est différente. Même lorsque $\alpha$ est faible, la distribution n'est pas nécessairement isotrope. La paroi impose une contrainte stérique : les grandes inclinaisons sont défavorisées parce qu'elles rapprochent une extrémité du bâtonnet de la surface. Cette idée est cohérente avec les travaux d'Atwi sur la couche de déplétion dans les mésopores.

Ainsi, les figures sous cisaillement linéaire montrent deux régimes :

- dans le bulk, le passage progressif d'un régime brownien vers un régime hydrodynamique ;
- près de la surface, une orientation déjà contrainte par la géométrie, ensuite modifiée par le cisaillement.

### Figures corrigées Fig1 et Fig2 du dossier `figures/`

Les figures `figures/Fig1_full_alpha0_linear_bulk.png` et `figures/Fig2_full_alpha0_linear_depletion.png` reprennent cette analyse avec l'ajout du cas $\alpha=0$.

Le cas $\alpha=0$ est physiquement important : il supprime la rotation hydrodynamique et conserve seulement la diffusion brownienne et le confinement géométrique. Dans le bulk, il sert de référence brownienne. Dans la couche de déplétion, il montre que la paroi peut déjà produire une organisation angulaire même sans cisaillement.

Cette comparaison permet de séparer proprement ce qui vient de l'écoulement et ce qui vient de la géométrie du mésopore.

## 3. Figures angulaires sous demi-profil parabolique

### Figures historiques Fig5-Fig8

Les figures historiques `Fig5.png` à `Fig8.png` concernent le demi-profil parabolique. La différence essentielle avec le cisaillement linéaire est que le taux de cisaillement local dépend de la position transverse :

$$
\alpha_{\mathrm{local}}(\xi)=\alpha(1-\xi).
$$

Cette relation doit être interprétée comme la dérivée locale du demi-profil de Poiseuille utilisé dans le code. Elle est cohérente avec la distinction discutée dans la thèse d'Atwi entre écoulement de Couette et écoulement de Poiseuille dans les canaux confinés.

Dans le bulk, la distribution $P(\theta)$ résulte d'une moyenne sur plusieurs valeurs locales de cisaillement. Les pics peuvent donc être plus larges ou moins monotones que dans le cas linéaire. Ce comportement n'est pas une anomalie : il traduit l'inhomogénéité spatiale du cisaillement.

Dans la couche de déplétion, deux effets se superposent : le cisaillement local, plus fort près de la paroi, et la sélection géométrique des orientations accessibles. La paroi continue donc à jouer un rôle majeur, même lorsque le profil d'écoulement est modifié.

### Figures corrigées Fig3 et Fig4 du dossier `figures/`

Les figures `figures/Fig3_full_alpha0_parabolic_bulk.png` et `figures/Fig4_full_alpha0_parabolic_depletion.png` montrent plus clairement le rôle du cas $\alpha=0$.

Dans le bulk, l'ajout de $\alpha=0$ permet d'identifier le niveau de référence brownien. Lorsque $\alpha$ augmente, la réponse hydrodynamique apparaît, mais elle reste modulée par la dépendance spatiale de $\alpha_{\mathrm{local}}$.

Près de la surface, le cas $\alpha=0$ confirme que la couche de déplétion n'est pas créée par le cisaillement. Elle existe déjà par contrainte géométrique. Le cisaillement parabolique modifie ensuite cette structure en ajoutant un couple hydrodynamique dépendant de la position.

## 4. Comparaisons entre cisaillement linéaire et parabolique

Les figures historiques `Fig9.png` à `Fig14.png` comparent les profils linéaire et parabolique pour des valeurs données de $\alpha$.

Dans le bulk, la différence entre les deux profils est directement liée à l'homogénéité du cisaillement. Le cisaillement linéaire impose le même $\alpha_{\mathrm{local}}$ à toutes les positions, ce qui conduit souvent à une orientation plus nette. Le demi-profil parabolique mélange au contraire des sous-populations soumises à des cisaillements locaux différents, ce qui élargit la distribution.

Près de la surface, la différence entre les deux profils est partiellement masquée par le confinement stérique. La paroi impose déjà une forte sélection angulaire ; le profil d'écoulement déplace ou affine cette distribution, mais ne remplace pas l'effet géométrique de la surface.

Cette lecture est très proche de la logique d'Atwi : dans les mésopores, les PDF ne dépendent pas seulement du champ d'écoulement, mais aussi de la position de la particule par rapport aux frontières solides.

## 5. Distributions spatiales $P(\xi)$ et couche de déplétion

Les figures `Fig15_corrected.png` à `Fig18_corrected.png`, ainsi que les figures `figures/Fig5a_raw_Pxi_linear.png`, `figures/Fig5b_binned_Pxi_linear.png`, `figures/Fig6a_raw_Pxi_parabolic.png` et `figures/Fig6b_binned_Pxi_parabolic.png`, sont essentielles car elles montrent la distribution spatiale du centre de masse.

La diminution de $P(\xi)$ près de la surface indique l'existence d'une couche de déplétion. Cette couche ne doit pas être interprétée comme une séparation de phase. Elle provient principalement de l'exclusion géométrique : lorsque le centre de masse est proche de la paroi, certaines orientations du bâtonnet deviennent impossibles.

Cette interprétation est directement cohérente avec la thèse d'Atwi, qui distingue les distributions dans le bulk et dans la couche de déplétion pour des particules confinées dans des mésopores.

Le traitement par binning, utilisé dans les figures corrigées, est un post-traitement statistique. Il réduit les oscillations numériques dues au comptage dans des bins trop fins. Il ne modifie ni la dynamique brownienne, ni le cisaillement, ni la géométrie. Il permet seulement de mieux faire apparaître la tendance physique robuste.

## 6. Courbes $\theta_{\max}(\alpha)$

Les figures `Fig19_theta_max_bulk.png`, `Fig20_theta_max_depletion_layer.png`, `figures/Fig7_theta_max_bulk.png` et `figures/Fig8_theta_max_depletion.png` résument l'évolution de l'angle le plus probable.

Dans le bulk, lorsque $\alpha$ augmente, $\theta_{\max}$ tend globalement à se rapprocher de la direction de l'écoulement. Cette tendance exprime la domination progressive du couple hydrodynamique sur la diffusion brownienne rotationnelle. Elle est cohérente avec l'interprétation du nombre de Péclet rotationnel.

Dans la couche de déplétion, $\theta_{\max}$ reste généralement proche de faibles angles. Cela ne signifie pas que le cisaillement est absent, mais que la paroi limite déjà fortement les orientations accessibles. La surface impose une pré-orientation géométrique, puis le cisaillement modifie cette orientation dans un domaine angulaire restreint.

Il est important de distinguer un maximum numérique d'un maximum physique. Pour une distribution large et peu contrastée, $\theta_{\max}$ peut varier sous l'effet de petites fluctuations statistiques. Pour une distribution étroite et fortement piquée, $\theta_{\max}$ devient un indicateur physique fiable de l'orientation préférentielle.

## 7. Lecture cinétique des résultats

Cinématiquement, les résultats peuvent être compris en termes de temps de résidence angulaire et spatial.

Lorsque le bâtonnet traverse rapidement certaines orientations sous l'effet du cisaillement, la probabilité associée à ces angles diminue. Lorsqu'il reste plus longtemps dans un domaine angulaire, $P(\theta)$ augmente dans ce domaine. Ainsi, $P(\theta)$ est aussi une mesure indirecte du temps moyen passé par le bâtonnet dans chaque orientation.

De même, $P(\xi)$ mesure le temps statistique passé par le centre de masse à chaque distance de la paroi. Une faible densité près de la surface signifie que les configurations correspondantes sont peu accessibles ou rapidement corrigées par les contraintes géométriques et les interactions de surface.

Cette lecture cinétique donne un sens physique aux histogrammes : chaque courbe est une projection statistique de la dynamique brownienne, hydrodynamique et confinée.

## 8. Ce qu'il faut dire au superviseur

Une formulation synthétique et solide serait :

> Les résultats ne doivent pas être lus comme de simples courbes numériques. Ils représentent des distributions stationnaires hors équilibre. Dans le bulk, la forme de $P(\theta)$ est principalement contrôlée par la compétition entre diffusion brownienne rotationnelle et cisaillement hydrodynamique. Près de la surface, cette compétition est modifiée par le confinement stérique, qui réduit l'espace des orientations accessibles et crée une couche de déplétion. Le paramètre $\alpha$ joue le rôle d'un nombre de Péclet rotationnel : lorsqu'il augmente, le cisaillement devient progressivement dominant. Dans le cas parabolique, l'interprétation est plus riche parce que le cisaillement local dépend de la position, ce qui produit une moyenne sur plusieurs environnements hydrodynamiques. Cette lecture est cohérente avec le cadre hors équilibre de Balakrishnan, l'approche de Boeder-Hijazi pour $P(\theta)$ et les travaux d'Atwi sur les particules confinées dans les mésopores.

## 9. Conclusion

L'ensemble des résultats montre que le système est gouverné par une dynamique statistique hors équilibre. Les distributions angulaires révèlent la compétition entre désordre brownien et orientation hydrodynamique. Les distributions spatiales révèlent l'effet du confinement et l'existence d'une couche de déplétion. Les courbes $\theta_{\max}(\alpha)$ synthétisent le passage progressif vers un régime orienté par le cisaillement.

Les références ne servent donc pas seulement à décorer le rapport. Elles structurent l'interprétation physique : Balakrishnan pour le cadre stochastique hors équilibre, Hijazi et Khater pour les distributions angulaires sous cisaillement, Atwi pour les mésopores, les parois et la couche de déplétion.
