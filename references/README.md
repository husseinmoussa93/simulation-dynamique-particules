# Références scientifiques et rôle dans le projet

Ce dossier résume le rôle des références utilisées pour interpréter les résultats numériques. Il ne remplace pas les articles ou thèses, mais indique comment chaque source soutient la lecture physique du modèle.

## Balakrishnan - Physique statistique hors équilibre

Balakrishnan fournit le cadre général : dynamique de Langevin, fluctuations browniennes, dissipation, processus stochastiques et états stationnaires hors équilibre.

Dans ce projet, cette référence justifie la lecture du code comme une dynamique forcée et fluctuante :

- le cisaillement est le forçage extérieur ;
- le mouvement brownien représente les fluctuations thermiques ;
- les histogrammes \(P(\theta)\) et \(P(\xi)\) sont des observables statistiques ;
- les résultats ne décrivent pas une trajectoire unique mais une distribution stationnaire.

Balakrishnan ne donne pas les équations spécifiques du bâtonnet sous cisaillement utilisées dans ce projet. Il fournit le cadre stochastique général.

## Hijazi, Khater, Tannous et Boeder - Macromolécules sous écoulement laminaire

Ces travaux sont au coeur de l'interprétation des distributions angulaires \(P(\theta)\).

Ils soutiennent les points suivants :

- une macromolécule allongée sous écoulement laminaire acquiert une orientation statistique privilégiée ;
- le cisaillement hydrodynamique entre en compétition avec la diffusion rotationnelle brownienne ;
- le paramètre \(\alpha\) joue le rôle d'un nombre de Péclet rotationnel ;
- les maxima de \(P(\theta)\) renseignent sur les orientations statistiquement dominantes.

## Thèse de Hijazi

La thèse de Hijazi est très proche du sujet de ce dépôt, car elle traite des densités de probabilité de macromolécules en solution sous écoulement laminaire.

Elle soutient directement l'idée de construire des histogrammes et distributions de probabilité plutôt que de limiter l'analyse à une trajectoire individuelle.

## Atwi - Mésopores, surfaces et couche de déplétion

Les travaux d'Atwi sont essentiels pour l'interprétation géométrique :

- distinction entre volume et zone proche de surface ;
- rôle du mésopore dans la sélection spatiale et angulaire ;
- influence des parois sur \(P(\theta)\) et \(P(\xi)\) ;
- importance des interactions de surface et des conditions de bord.

Ces références soutiennent les Sections II et III du dépôt, où l'on étudie respectivement le rapport \(D/L_B\) et les coefficients de restitution.

## Synthèse

Le projet combine trois niveaux d'interprétation :

1. un cadre stochastique hors équilibre ;
2. une orientation hydrodynamique sous cisaillement ;
3. une sélection géométrique et dynamique imposée par les surfaces du mésopore.

Les résultats numériques doivent donc toujours être lus comme la conséquence conjointe du bruit brownien, du cisaillement, de la géométrie et des conditions de bord.
