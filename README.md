# Simulation numérique d'un bâtonnet brownien confiné

Ce dépôt présente une simulation numérique en C++ de la dynamique d'un bâtonnet brownien rigide confiné dans un mésopore. Le but physique est d'étudier comment un écoulement de cisaillement, le mouvement brownien et la proximité d'une surface modifient l'orientation et la position transverse de la particule.

La version actuelle compare deux profils d'écoulement :

- un cisaillement linéaire uniforme ;
- un demi-profil parabolique de type Poiseuille.

Les simulations sont effectuées pour les valeurs suivantes du paramètre de contrôle :

$$
\alpha = 0,\ 0.5,\ 1,\ 2,\ 5,\ 10,\ 100.
$$

La valeur $\alpha = 0$ sert de référence sans cisaillement hydrodynamique. Elle permet de distinguer ce qui vient uniquement du confinement géométrique et de la diffusion brownienne de ce qui est réellement produit par l'écoulement.

---

## 1. Modèle physique

Le système étudié est un bâtonnet rigide de longueur $L_B$ confiné près d'une surface. Dans le code utilisé ici :

$$
L_B = D = 880\ \mathrm{nm}.
$$

La position transverse du centre de masse est notée $z_c$. On introduit la position réduite :

$$
\xi = \frac{z_c}{L_B}.
$$

Comme $D = L_B$, la variable $\xi$ varie entre 0 et 1 dans la géométrie actuelle. La surface inférieure correspond à $\xi = 0$, tandis que la zone éloignée de la surface correspond à $\xi > 0.5$.

Deux régions statistiques sont séparées :

$$
\xi \leq 0.5 \quad \text{: couche de déplétion, proche de la surface},
$$

$$
\xi > 0.5 \quad \text{: volume}.
$$

L'angle d'orientation du bâtonnet est noté $\theta$. Il est mesuré par rapport à la direction de l'écoulement, avec :

$$
-90^\circ \leq \theta < 90^\circ.
$$

Lorsque $\theta$ est proche de $0^\circ$, le bâtonnet est presque parallèle aux lignes de courant et à la surface. Lorsque $|\theta|$ augmente, le bâtonnet devient plus incliné et risque davantage d'interagir avec la paroi.

---

## 2. Dynamique simulée

La dynamique résulte de trois contributions principales.

La première est la diffusion rotationnelle brownienne. Elle modélise les fluctuations thermiques du fluide et tend à désordonner l'orientation du bâtonnet :

$$
\Delta \theta_B = \pm \Delta_B.
$$

La deuxième est la diffusion translationnelle brownienne suivant $z_c$. Elle déplace le centre de masse dans la direction transverse :

$$
\Delta z_B = \pm \frac{L_B}{3}\Delta_B.
$$

La troisième est la rotation hydrodynamique induite par le cisaillement :

$$
\Delta \theta_H =
-\frac{\alpha_{\mathrm{local}}}{2}\sin^2(\theta)\Delta_B^2.
$$

Cette relation exprime le fait que le cisaillement n'agit pas comme un bruit aléatoire, mais comme un terme déterministe qui favorise certaines orientations.

Le paramètre $\alpha$ joue le rôle d'un nombre de Péclet rotationnel :

$$
\alpha \sim \frac{\dot{\gamma}_0}{D_{\mathrm{rot}}}.
$$

Il compare l'effet du cisaillement hydrodynamique à la diffusion rotationnelle brownienne. Lorsque $\alpha$ est petit, le mouvement brownien domine. Lorsque $\alpha$ est grand, l'écoulement impose progressivement une orientation préférentielle.

---

## 3. Profils de cisaillement

### 3.1 Cisaillement linéaire

Dans le cas linéaire, le cisaillement est supposé uniforme dans la zone étudiée :

$$
\alpha_{\mathrm{local}} = \alpha.
$$

Chaque position transverse ressent donc la même intensité de cisaillement.

### 3.2 Demi-profil parabolique

Dans le cas parabolique, la simulation utilise un cisaillement local dépendant de la position :

$$
\alpha_{\mathrm{local}}(\xi) = \alpha(1-\xi).
$$

Ce choix correspond à un demi-profil de Poiseuille. Dans un écoulement de Poiseuille entre deux parois, la vitesse est parabolique et le taux de cisaillement est proportionnel à la dérivée de cette vitesse. Sur une moitié du canal, le cisaillement local décroît linéairement lorsqu'on s'éloigne de la paroi.

Ainsi, près de la surface, le cisaillement local est plus fort. Vers la région $\xi \simeq 1$, il devient plus faible. Cela explique pourquoi les distributions obtenues sous demi-profil parabolique sont souvent plus larges ou plus irrégulières : elles résultent d'une moyenne sur plusieurs valeurs locales de cisaillement.

---

## 4. Grandeurs statistiques calculées

La simulation produit trois familles principales de grandeurs.

La première est la distribution angulaire dans le volume :

$$
P(\theta)\quad \text{pour}\quad \xi > 0.5.
$$

La deuxième est la distribution angulaire dans la couche de déplétion :

$$
P(\theta)\quad \text{pour}\quad \xi \leq 0.5.
$$

La troisième est la distribution spatiale transverse :

$$
P(\xi)\quad \text{pour}\quad 0 \leq \xi \leq 1.
$$

Pour les distributions spatiales, une représentation normalisée est aussi utilisée :

$$
\frac{\rho(\xi)}{\rho_{\mathrm{bulk}}}.
$$

Cette normalisation compare la densité locale à la densité moyenne dans le volume. Elle permet de visualiser clairement la couche de déplétion : si $\rho(\xi)/\rho_{\mathrm{bulk}} < 1$, la région est statistiquement appauvrie en centres de masse.

---

## 5. Distributions angulaires sous cisaillement linéaire

### Figure 1 : distribution angulaire dans le volume

![Figure 1](figures/Fig1_full_alpha0_linear_bulk.png)

La Figure 1 montre $P(\theta)$ dans le volume pour un cisaillement linéaire. Dans cette région, le bâtonnet est moins contraint par la surface et peut explorer un domaine angulaire plus large.

Pour $\alpha = 0$, il n'y a pas de rotation hydrodynamique. La distribution constitue donc une référence brownienne. En volume, aucun alignement imposé par le cisaillement ne doit être attendu.

Lorsque $\alpha$ augmente, la distribution devient progressivement anisotrope. Les faibles valeurs de $\alpha$ correspondent à une compétition entre la diffusion rotationnelle brownienne et le couple hydrodynamique. Aux grandes valeurs, en particulier $\alpha = 10$ et $\alpha = 100$, l'effet de l'écoulement devient dominant : la probabilité se concentre autour d'un intervalle angulaire plus étroit.

Le déplacement du maximum vers des angles plus proches de $0^\circ$ indique que le bâtonnet tend à s'aligner avec les lignes de courant lorsque le nombre de Péclet rotationnel augmente.

### Figure 2 : distribution angulaire dans la couche de déplétion

![Figure 2](figures/Fig2_full_alpha0_linear_depletion.png)

La Figure 2 présente $P(\theta)$ près de la surface. La différence essentielle avec le volume est la présence de la contrainte stérique imposée par la paroi.

Même lorsque $\alpha = 0$, le bâtonnet ne peut pas adopter librement toutes les orientations. Les grandes inclinaisons augmentent le risque d'intersection avec la surface. La géométrie favorise donc naturellement les orientations presque parallèles à la paroi, c'est-à-dire proches de $\theta = 0^\circ$.

Lorsque $\alpha$ augmente, le cisaillement renforce cette orientation préférentielle. Cependant, dans la couche de déplétion, l'effet dominant n'est pas seulement hydrodynamique : il est aussi géométrique. La paroi réduit l'espace des orientations accessibles avant même que le cisaillement n'agisse fortement.

Cette figure montre donc une compétition entre deux mécanismes : le confinement stérique, qui existe même à $\alpha = 0$, et le cisaillement linéaire, qui devient plus visible lorsque $\alpha$ augmente.

---

## 6. Distributions angulaires sous demi-profil parabolique

### Figure 3 : distribution angulaire dans le volume

![Figure 3](figures/Fig3_full_alpha0_parabolic_bulk.png)

La Figure 3 montre $P(\theta)$ dans le volume pour le demi-profil parabolique. Contrairement au cisaillement linéaire, le taux de cisaillement local n'est pas constant :

$$
\alpha_{\mathrm{local}}(\xi) = \alpha(1-\xi).
$$

Le volume contient donc des particules situées à différentes positions $\xi$, chacune ressentant une intensité hydrodynamique différente. La distribution globale est une superposition de sous-populations soumises à des cisaillements locaux distincts.

Cette inhomogénéité explique pourquoi les pics sont généralement moins simples à interpréter que dans le cas linéaire. Aux faibles valeurs de $\alpha$, les maxima numériques peuvent être influencés par le bruit statistique et par la largeur des distributions. Aux fortes valeurs, l'orientation devient plus nette, mais elle reste marquée par la variation spatiale du cisaillement.

La figure met donc en évidence une dynamique hors équilibre plus complexe : le bâtonnet ne subit pas seulement une compétition entre diffusion brownienne et cisaillement, mais aussi une variation de l'intensité du cisaillement selon sa position.

### Figure 4 : distribution angulaire dans la couche de déplétion

![Figure 4](figures/Fig4_full_alpha0_parabolic_depletion.png)

La Figure 4 correspond à la couche de déplétion sous demi-profil parabolique. Cette région est physiquement importante parce qu'elle combine deux effets forts : la proximité de la surface et un cisaillement local élevé.

La surface impose une sélection géométrique des orientations. Le demi-profil parabolique ajoute ensuite une rotation hydrodynamique dépendante de la position. Le résultat est une distribution centrée près des faibles angles, avec une évolution progressive lorsque $\alpha$ augmente.

Comparée au volume, la couche de déplétion présente des orientations beaucoup plus contraintes. Le bâtonnet ne peut pas explorer librement les grands angles, car ceux-ci le rapprochent mécaniquement de la paroi. La paroi agit donc comme un filtre géométrique sur l'espace angulaire accessible.

---

## 7. Distributions spatiales : données brutes et traitement statistique

Les Figures 5a et 6a présentent les distributions spatiales brutes $P(\xi)$. Elles montrent directement le résultat du comptage dans des bins fins. Les oscillations visibles, surtout pour les grandes valeurs de $\alpha$, proviennent du nombre fini d'échantillons et de la finesse du pas en $\xi$.

Pour faire apparaître la tendance physique robuste, les Figures 5b et 6b utilisent un regroupement statistique de cinq bins successifs :

$$
\Delta \xi = 0.005.
$$

Ce traitement ne modifie pas la dynamique simulée. Il agit uniquement comme un post-traitement statistique destiné à réduire les oscillations de comptage et à rendre la couche de déplétion plus lisible.

### Figure 5a : distribution spatiale brute sous cisaillement linéaire

![Figure 5a](figures/Fig5a_raw_Pxi_linear.png)

La Figure 5a montre la distribution spatiale brute $P(\xi)$ pour le cisaillement linéaire. Le profil croît depuis la surface jusqu'à la région du volume. Cette croissance traduit l'existence d'une couche de déplétion : près de la paroi, une partie des positions du centre de masse est géométriquement moins accessible à cause de la longueur finie du bâtonnet.

Le saut autour de $\xi \simeq 0.5$ correspond au passage entre la région proche de la surface et le volume. Dans le volume, la densité devient beaucoup plus proche d'un plateau.

### Figure 5b : distribution spatiale normalisée sous cisaillement linéaire

![Figure 5b](figures/Fig5b_binned_Pxi_linear.png)

La Figure 5b montre la même information après regroupement statistique et normalisation par $\rho_{\mathrm{bulk}}$.

La lecture physique devient plus claire : la quantité $\rho(\xi)/\rho_{\mathrm{bulk}}$ est faible près de la surface, puis augmente progressivement jusqu'à atteindre une valeur proche de 1 dans le volume. Cela signifie que la densité locale rejoint la densité moyenne du volume lorsque le centre de masse est suffisamment éloigné de la paroi.

Cette figure confirme que l'effet principal sur $P(\xi)$ est géométrique. Le cisaillement modifie légèrement les profils, mais la forme générale de la couche de déplétion est imposée par l'exclusion stérique du bâtonnet près de la surface.

### Figure 6a : distribution spatiale brute sous demi-profil parabolique

![Figure 6a](figures/Fig6a_raw_Pxi_parabolic.png)

La Figure 6a présente la distribution spatiale brute $P(\xi)$ pour le demi-profil parabolique. Comme dans le cas linéaire, la densité est faible près de la surface et augmente vers le volume.

Les oscillations brutes sont visibles parce que la statistique est collectée avec un pas fin en $\xi$. Elles ne doivent pas être interprétées comme des structures physiques périodiques. Elles sont liées à la discrétisation de l'histogramme et au caractère aléatoire de la dynamique brownienne.

### Figure 6b : distribution spatiale normalisée sous demi-profil parabolique

![Figure 6b](figures/Fig6b_binned_Pxi_parabolic.png)

La Figure 6b montre la distribution spatiale normalisée après regroupement statistique. Comme dans le cas linéaire, la courbe révèle clairement une région appauvrie près de la surface et un plateau dans le volume.

La différence physique avec le cisaillement linéaire vient du fait que le cisaillement local dépend de $\xi$. Le bâtonnet proche de la surface ressent un cisaillement plus fort que celui situé plus loin. Malgré cela, la forme globale de $\rho(\xi)/\rho_{\mathrm{bulk}}$ reste dominée par le confinement stérique.

---

## 8. Évolution de l'angle le plus probable

L'angle $\theta_{\max}$ est défini comme le centre du bin angulaire où la probabilité $P(\theta)$ est maximale.

Il faut cependant distinguer deux situations :

- si la distribution est fortement piquée, $\theta_{\max}$ correspond à une orientation préférentielle physiquement significative ;
- si la distribution est large ou presque uniforme, $\theta_{\max}$ est seulement un maximum numérique, parfois produit par de faibles fluctuations statistiques.

Pour cette raison, les courbes $\theta_{\max}(\alpha)$ sont tracées uniquement pour les valeurs positives de $\alpha$. La valeur $\alpha = 0$ est une référence sans cisaillement, mais elle ne définit pas un maximum hydrodynamique pertinent dans le volume.

### Figure 7 : variation de $\theta_{\max}$ dans le volume

![Figure 7](figures/Fig7_theta_max_bulk.png)

La Figure 7 montre la variation de $\theta_{\max}$ en fonction de $\alpha$ dans le volume.

Dans le cas du cisaillement linéaire, la tendance générale est une diminution de $\theta_{\max}$ lorsque $\alpha$ augmente. Physiquement, cela signifie que le bâtonnet s'oriente de plus en plus près de la direction de l'écoulement. À grand $\alpha$, le couple hydrodynamique domine la diffusion brownienne rotationnelle et impose un alignement plus marqué.

Dans le cas du demi-profil parabolique, l'évolution est moins monotone aux faibles et moyennes valeurs de $\alpha$. Cette irrégularité n'est pas surprenante : le volume mélange des particules soumises à différents cisaillements locaux. De plus, lorsque les distributions sont larges, le maximum numérique peut se déplacer sans correspondre à une orientation physique très nette.

À grande valeur de $\alpha$, la tendance redevient plus claire : le maximum se rapproche de faibles angles, ce qui traduit l'orientation progressive du bâtonnet par l'écoulement.

### Figure 8 : variation de $\theta_{\max}$ dans la couche de déplétion

![Figure 8](figures/Fig8_theta_max_depletion.png)

La Figure 8 montre l'évolution de $\theta_{\max}$ dans la couche de déplétion.

Contrairement au volume, les valeurs de $\theta_{\max}$ restent proches de faibles angles. Cela confirme que la surface impose une orientation presque parallèle à la paroi. Le cisaillement peut déplacer légèrement le maximum, mais il agit dans un espace angulaire déjà fortement contraint.

Cette figure montre donc que la couche de déplétion n'est pas simplement une version plus dense ou moins dense du volume. Elle correspond à un régime physique différent, dominé par l'interaction entre confinement stérique, diffusion brownienne et cisaillement local.

---

## 9. Valeurs numériques de $\theta_{\max}$

Les valeurs suivantes ont été extraites des histogrammes angulaires. Elles doivent être lues comme des maxima numériques. Leur signification physique est forte lorsque la distribution est étroite et contrastée, et plus faible lorsque la distribution est large.

### Volume

| $\alpha$ | Cisaillement linéaire | Demi-profil parabolique |
|---:|---:|---:|
| 0.5 | 32.5° | 60.5° |
| 1 | 36.5° | 31.5° |
| 2 | 32.5° | 57.5° |
| 5 | 25.5° | 36.5° |
| 10 | 20.5° | 34.5° |
| 100 | 9.5° | 14.5° |

### Couche de déplétion

| $\alpha$ | Cisaillement linéaire | Demi-profil parabolique |
|---:|---:|---:|
| 0.5 | -1.5° | 1.5° |
| 1 | 1.5° | 3.5° |
| 2 | 5.5° | 0.5° |
| 5 | 11.5° | 3.5° |
| 10 | 11.5° | 9.5° |
| 100 | 7.5° | 10.5° |

---

## 10. Conclusion physique

Les résultats montrent que l'orientation du bâtonnet est gouvernée par trois mécanismes :

- la diffusion rotationnelle brownienne, qui tend à désordonner l'orientation ;
- le cisaillement hydrodynamique, qui favorise une orientation préférentielle ;
- le confinement stérique, qui limite les orientations possibles près de la surface.

Dans le volume, l'augmentation de $\alpha$ conduit progressivement à une orientation plus marquée du bâtonnet par l'écoulement. Cette tendance est plus directe dans le cas linéaire, car le cisaillement est uniforme.

Dans la couche de déplétion, la paroi joue un rôle dominant. Même sans cisaillement, elle favorise les orientations presque parallèles à la surface. Le cisaillement modifie ensuite cette organisation, mais ne remplace pas la contrainte géométrique.

Les distributions spatiales $P(\xi)$ confirment l'existence d'une couche appauvrie près de la surface. Cette couche n'est pas une séparation de phase : elle correspond à une exclusion géométrique due à la taille finie du bâtonnet et à l'impossibilité d'occuper certaines configurations proches de la paroi.

La comparaison entre les données brutes et les profils regroupés montre enfin l'importance du post-traitement statistique. Le regroupement des bins réduit les oscillations numériques sans modifier le modèle physique, ce qui permet de mieux distinguer les tendances robustes.

---

## 11. Fichiers principaux

- `main.cpp` : code C++ complet de la simulation.
- `figures/` : figures finales utilisées pour l'interprétation physique.
- `data/` : fichiers numériques post-traités pour les figures $\theta_{\max}(\alpha)$ et $\rho(\xi)/\rho_{\mathrm{bulk}}$.

Le programme écrit ses résultats dans le dossier :

```text
results_alpha0_full
```

Les principaux fichiers générés suivent les formes :

```text
teta_bulk_<profil>_alpha_<valeur>.txt
teta_surface_<profil>_alpha_<valeur>.txt
ksi_surface_<profil>_alpha_<valeur>.txt
ksi_full_<profil>_alpha_<valeur>.txt
```

où `<profil>` vaut `linear` ou `parabolic`, et `<valeur>` vaut `0`, `0p5`, `1`, `2`, `5`, `10` ou `100`.

---

## 12. Note méthodologique

Les résultats présentés ici correspondent à une simulation stochastique à graines pseudo-aléatoires fixes. Ce choix rend les comparaisons reproductibles. Pour une étude statistique plus complète, il serait utile de répéter les simulations avec plusieurs jeux de graines indépendantes et d'ajouter des barres d'incertitude sur les histogrammes et sur $\theta_{\max}$.

Une amélioration future importante serait également d'étudier d'autres rapports entre le diamètre du mésopore et la longueur du bâtonnet, notamment le cas où le diamètre du mésopore devient inférieur à la longueur du bâtonnet.
