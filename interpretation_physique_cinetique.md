# Interprétation physique et cinétique des résultats

Ce document complète le rapport principal du dépôt. Son objectif est de donner une lecture physique et cinétique cohérente des distributions numériques obtenues pour un bâtonnet brownien confiné dans un mésopore et soumis à un écoulement de cisaillement. L'interprétation s'appuie sur le cadre de la physique statistique hors équilibre, sur les travaux relatifs à l'équation de Boeder et sur les études de particules anisotropes confinées dans des mésopores.

## 1. Cadre physique général

Le système étudié est un exemple de **dynamique statistique hors équilibre**. Le bâtonnet est soumis simultanément à trois mécanismes :

- la **diffusion brownienne rotationnelle**, qui tend à désordonner l'orientation ;
- le **cisaillement hydrodynamique**, qui produit un couple déterministe orientant le bâtonnet ;
- le **confinement stérique**, qui limite les configurations accessibles près de la paroi.

Dans le langage de la physique statistique, les trajectoires individuelles ne sont pas l'objet principal de l'analyse. Ce qui est physiquement significatif est la distribution de probabilité stationnaire : $P(\theta)$ pour l'orientation et $P(\xi)$ pour la position transverse réduite. Cette approche est cohérente avec le cadre de Langevin et de Fokker-Planck présenté par Balakrishnan, où l'évolution microscopique aléatoire conduit à des grandeurs statistiques macroscopiquement interprétables.

La simulation produit donc une image statistique du système : elle ne cherche pas à prédire une trajectoire unique du bâtonnet, mais la probabilité d'observer certaines orientations et certaines positions après un grand nombre d'événements brownien-hydrodynamiques.

## 2. Rôle du nombre de Péclet rotationnel

Le paramètre central du modèle est :

$$
\alpha = \frac{\dot{\gamma}_0}{D_{\mathrm{rot}}}.
$$

Il compare l'intensité du cisaillement hydrodynamique au coefficient de diffusion rotationnelle brownienne. Il joue donc le rôle d'un **nombre de Péclet rotationnel**.

Pour $\alpha \ll 1$, la diffusion brownienne rotationnelle domine. Le bâtonnet explore un grand domaine angulaire et la distribution $P(\theta)$ reste large, parfois presque uniforme. Dans ce régime, un maximum numérique peut apparaître dans l'histogramme, mais il ne correspond pas nécessairement à une orientation physique privilégiée.

Pour $\alpha \gg 1$, le couple hydrodynamique domine. Le bâtonnet est davantage entraîné par le cisaillement et passe plus de temps dans des orientations proches de la direction de l'écoulement. La distribution $P(\theta)$ devient plus anisotrope, plus piquée, et le maximum $\theta_{\max}$ devient physiquement plus significatif.

Cette lecture est directement reliée aux travaux de Boeder, puis aux analyses de Khater, Tannous et Hijazi sur les distributions angulaires de macromolécules allongées en écoulement.

## 3. Signification de $P(\theta)$

La distribution $P(\theta)$ mesure la probabilité d'observer le bâtonnet avec une orientation $\theta$ par rapport à la direction de l'écoulement.

Une distribution large signifie que le bâtonnet explore de nombreuses orientations. Cela indique un régime où la diffusion brownienne reste importante. Une distribution étroite indique au contraire que certaines orientations sont fortement favorisées, généralement sous l'effet du cisaillement hydrodynamique ou du confinement près de la paroi.

Le maximum de la distribution, noté $\theta_{\max}$, doit être interprété avec prudence :

- si $P(\theta)$ est large et faiblement contrastée, $\theta_{\max}$ est essentiellement un maximum numérique ;
- si $P(\theta)$ présente un pic net et stable, $\theta_{\max}$ correspond à une orientation préférentielle physiquement significative.

Cette distinction est essentielle pour éviter une surinterprétation des résultats à faible $\alpha$. Dans un régime dominé par le bruit brownien, une petite fluctuation statistique peut déplacer le maximum apparent sans traduire un véritable alignement du bâtonnet.

## 4. Interprétation cinétique de $P(\theta)$

Cinématiquement, l'orientation du bâtonnet évolue par l'alternance de deux contributions.

La première est la rotation brownienne. Elle est aléatoire, change de signe, et traduit les impacts microscopiques du fluide sur la particule. Cette contribution élargit $P(\theta)$.

La deuxième est la rotation hydrodynamique. Elle est déterministe et dépend du cisaillement local. Dans le modèle utilisé, elle tend à orienter progressivement le bâtonnet avec l'écoulement. Cette contribution resserre $P(\theta)$ et déplace le maximum vers des angles plus faibles lorsque $\alpha$ devient grand.

L'état observé dans les histogrammes est donc un équilibre dynamique hors équilibre : le bâtonnet n'est ni complètement désordonné, ni parfaitement aligné. Il se trouve dans une situation stationnaire où l'agitation brownienne et le couple hydrodynamique se compensent statistiquement.

## 5. Bulk et couche de déplétion

La distinction entre le **bulk** et la **couche de déplétion** est centrale dans l'interprétation.

Dans le bulk, le bâtonnet est relativement loin de la surface. Il dispose d'un espace angulaire plus large et peut explorer davantage d'orientations. Les distributions $P(\theta)$ y reflètent surtout la compétition entre diffusion brownienne rotationnelle et cisaillement hydrodynamique.

Dans la couche de déplétion, la situation est différente. La proximité de la paroi impose une contrainte géométrique forte : les grandes inclinaisons augmentent le risque de contact avec la surface. Certaines configurations deviennent donc moins accessibles, voire interdites. Le bâtonnet tend alors à adopter des orientations plus parallèles à la paroi.

Cette couche ne doit pas être interprétée comme une séparation de phase. Elle correspond à une exclusion géométrique liée à la taille finie du bâtonnet. Cette idée est cohérente avec les travaux d'Atwi sur les particules confinées dans les mésopores, où les PDF sont étudiées séparément dans le bulk et dans la région proche des parois.

## 6. Signification de $P(\xi)$

La variable $\xi$ représente la position transverse réduite du centre de masse du bâtonnet. La distribution $P(\xi)$ indique donc où le centre de masse passe le plus de temps dans le mésopore.

Lorsque $P(\xi)$ est faible près de la paroi, cela ne signifie pas que la particule est repoussée par une force répulsive explicite dans le code. Dans le modèle actuel, l'effet principal est stérique : près de la surface, le nombre de configurations géométriquement accessibles diminue. Le centre de masse ne peut pas occuper certaines positions si l'orientation du bâtonnet entraînerait une intersection avec la paroi.

Ainsi, la diminution de $P(\xi)$ près de la surface est la signature d'une couche appauvrie, ou **couche de déplétion**, produite par le confinement géométrique.

Le regroupement statistique des bins de $P(\xi)$ ne change pas la physique du modèle. Il réduit seulement les oscillations numériques dues au bruit d'échantillonnage. Les figures brutes montrent la sortie directe de la simulation, tandis que les figures regroupées permettent de mieux visualiser la tendance physique robuste.

## 7. Cisaillement linéaire et demi-profil parabolique

Dans le cas du cisaillement linéaire, le taux de cisaillement local est constant :

$$
\alpha_{\mathrm{local}} = \alpha.
$$

Toutes les particules subissent donc la même intensité d'entraînement hydrodynamique, indépendamment de leur position transverse. Les tendances de $P(\theta)$ sont alors plus directement lisibles : lorsque $\alpha$ augmente, l'alignement hydrodynamique devient plus fort.

Dans le cas du demi-profil parabolique utilisé dans la simulation, le taux de cisaillement local dépend de la position :

$$
\alpha_{\mathrm{local}}(\xi)=\alpha(1-\xi).
$$

Le profil de vitesse est parabolique, mais son gradient est linéaire. Le bâtonnet ne subit donc pas la même intensité de cisaillement selon sa position. Les distributions globales résultent d'une moyenne sur plusieurs environnements locaux. Cette inhomogénéité explique pourquoi certains pics sont plus larges, moins monotones ou plus difficiles à interpréter que dans le cas du cisaillement uniforme.

La thèse d'Atwi est particulièrement utile ici, car elle discute les particules confinées en écoulement de Poiseuille dans des mésopores et la distinction entre la zone centrale et les régions proches des parois.

## 8. Lecture physique des courbes $\theta_{\max}(\alpha)$

Les courbes $\theta_{\max}(\alpha)$ résument l'évolution de l'orientation la plus probable lorsque l'intensité du cisaillement augmente.

Dans le bulk, une diminution de $\theta_{\max}$ avec $\alpha$ indique que le bâtonnet s'oriente progressivement vers la direction de l'écoulement. Cette tendance est attendue lorsque le couple hydrodynamique devient plus fort que la diffusion brownienne rotationnelle.

Dans la couche de déplétion, $\theta_{\max}$ reste généralement proche de faibles angles, car la paroi impose déjà une orientation presque parallèle à la surface. Le cisaillement agit donc sur une distribution précontrainte par la géométrie.

Il faut cependant distinguer les maxima fiables des maxima faibles. Pour des distributions presque plates, surtout à faible $\alpha$, $\theta_{\max}$ est un indicateur numérique mais pas nécessairement un marqueur d'orientation physique forte.

## 9. Interprétation des oscillations statistiques

Les oscillations visibles dans certaines distributions, notamment dans $P(\xi)$, proviennent principalement de l'échantillonnage statistique et de la finesse des bins. Elles ne doivent pas être interprétées comme des structures physiques microscopiques tant qu'elles ne sont pas robustes lorsque l'on change la taille des bins ou les graines pseudo-aléatoires.

Le traitement par binning plus large consiste à regrouper plusieurs classes voisines. Cette opération diminue la variance statistique de chaque point. Elle conserve la tendance physique globale, mais réduit les fluctuations locales non significatives.

Dans le rapport, il est donc utile de présenter les données brutes puis les données regroupées. Les premières montrent la transparence numérique du calcul ; les secondes donnent une représentation plus claire de la tendance physique.

## 10. Lien avec les références

Balakrishnan fournit le cadre général : bruit brownien, dynamique de Langevin, équation de Fokker-Planck, état stationnaire et diffusion dans un domaine fini.

La thèse de Hijazi et les travaux associés à Boeder fournissent le cadre spécifique de $P(\theta)$ pour des macromolécules allongées en écoulement laminaire.

La thèse d'Atwi fournit le lien le plus direct avec les mésopores, les couches de déplétion, les collisions avec les parois, le coefficient de restitution et les interactions de Hamaker. Elle sera particulièrement importante pour les extensions du projet lorsque le diamètre du mésopore deviendra comparable ou inférieur à la longueur du bâtonnet, puis lorsque le coefficient de restitution sera étudié comme paramètre physique.

## 11. Conclusion générale

Les résultats numériques doivent être compris comme des distributions stationnaires hors équilibre. Leur forme est gouvernée par une compétition entre diffusion brownienne, cisaillement hydrodynamique et confinement stérique. Le bulk révèle principalement la compétition entre désordre brownien et orientation hydrodynamique. La couche de déplétion révèle en plus l'effet sélectif de la paroi sur les configurations accessibles.

Cette lecture permet de donner un sens physique aux histogrammes, aux pics, aux courbes $\theta_{\max}(\alpha)$ et aux distributions spatiales $P(\xi)$, tout en évitant de confondre fluctuations numériques, maxima apparents et mécanismes physiques réellement robustes.
