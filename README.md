## 1. Distribution Angulaire sous Écoulement Linéaire (Volume)

![Distribution Angulaire](Fig1.png)

### Interprétation Physique détaillée

### Figure 1 : Distribution angulaire $P(\theta)$ dans le volume pour un cisaillement linéaire

La **Figure 1** représente la distribution angulaire $P(\theta)$ d’un bâtonnet brownien dans le volume, défini ici par la condition $\xi > 0.5$, pour un cisaillement linéaire et pour trois valeurs du paramètre adimensionnel $\alpha$ : $\alpha = 0.5$, $\alpha = 2$ et $\alpha = 5$.

Le paramètre $\alpha$ mesure l’importance relative du cisaillement hydrodynamique par rapport à la diffusion rotationnelle brownienne. Il peut donc être interprété comme un nombre de Péclet rotationnel : lorsque $\alpha$ est faible, l’agitation brownienne domine ; lorsque $\alpha$ augmente, l’effet du cisaillement devient de plus en plus important dans la dynamique d’orientation du bâtonnet.

* **Pour $\alpha = 0.5$ :** La distribution angulaire est presque uniforme sur l’intervalle étudié. Cela signifie que le cisaillement est encore trop faible pour imposer une orientation préférentielle nette au bâtonnet. Dans ce régime, la diffusion rotationnelle brownienne domine la dynamique : le bâtonnet explore un large domaine d’angles sous l’effet des fluctuations thermiques. Les faibles ondulations visibles sur la courbe ne doivent pas être interprétées comme des maxima physiques significatifs, mais plutôt comme des fluctuations statistiques liées à la simulation numérique. Ainsi, pour $\alpha = 0.5$, aucun maximum physique bien défini ne peut être identifié.

* **Pour $\alpha = 2$ :** Lorsque $\alpha$ augmente à $\alpha = 2$, la distribution devient clairement anisotrope. Un maximum plus marqué apparaît autour de $\theta \approx 32.5^\circ$. Cette apparition d’une orientation préférentielle traduit la compétition entre deux mechanisms physiques : d’une part, la diffusion rotationnelle brownienne, qui tend à désordonner l’orientation du bâtonnet, et d’autre part, le couple hydrodynamique induit par le cisaillement, qui favorise certaines orientations par rapport à l’écoulement. Le système n’est donc plus isotrope : le bâtonnet passe davantage de temps dans une zone angulaire privilégiée.

* **Pour $\alpha = 5$ :** Pour $\alpha = 5$, l’effet du cisaillement devient encore plus dominant. La distribution présente un pic plus élevé et plus étroit, avec un maximum situé autour de $\theta \approx 25.5^\circ$. La diminution de la largeur du pic montre que les orientations du bâtonnet sont davantage concentrations autour d’un domaine angulaire restreint. Physiquement, cela signifie que le cisaillement contrôle plus fortement la dynamique rotationnelle et réduit l’effet désordonnant de l’agitation brownienne. Le déplacement du maximum vers des angles plus proches de la direction de l’écoulement traduit une tendance progressive à l’alignement du bâtonnet sous l’action du cisaillement.

---

> 📌 **Analyse de l'Asymétrie et Conclusion :**
> On observe également que les probabilités associées aux angles négatifs diminuent lorsque $\alpha$ augmente. Cette asymétrie est cohérente avec la dynamique hydrodynamique du modèle : le cisaillement entraîne une rotation orientée du bâtonnet, de sorte que certaines orientations sont traversées rapidement tandis que d’autres sont occupées plus longtemps. La distribution $P(\theta)$ reflète donc le temps moyen passé par le bâtonnet dans chaque intervalle angulaire.
>
> En conclusion, cette figure met en évidence la transition progressive entre un régime dominé par le mouvement brownien rotationnel, pour faible $\alpha$, et un régime dominé par le cisaillement hydrodynamique, pour des valeurs plus grandes de $\alpha$. 
> Les maxima physiquement significatifs sont observés autour de $\theta_{\max} \approx 32.5^\circ$ pour $\alpha = 2$ et $\theta_{\max} \approx 25.5^\circ$ pour $\alpha = 5$. Pour $\alpha = 0.5$, la distribution reste quasi uniforme et ne présente pas de maximum physique bien défini.
>
> ## 2. Distribution angulaire près de la surface pour un cisaillement linéaire

![Distribution angulaire près de la surface](Fig2.png)

### Interprétation physique

La **Figure 2** représente la distribution angulaire $P(\theta)$ du bâtonnet près de la surface, définie par la condition $\xi \leq 0.5$, pour un cisaillement linéaire et pour trois valeurs du paramètre $\alpha$ : $\alpha = 0.5$, $\alpha = 2$ et $\alpha = 5$.

Contrairement au cas du volume ($\xi > 0.5$), la distribution angulaire près de la surface n’est pas uniforme, même pour une faible valeur de $\alpha = 0.5$. Cela montre que la présence de la paroi joue un rôle physique essentiel dans l’orientation du bâtonnet. Lorsque le centre du bâtonnet est proche de la surface, certaines orientations deviennent géométriquement défavorables, car une inclinaison trop grande pourrait conduire à une intersection du bâtonnet avec la paroi. La surface impose donc une contrainte stérique qui favorise les orientations presque parallèles à la paroi, c’est-à-dire des angles proches de $\theta = 0^\circ$.

* **Pour $\alpha = 0.5$ :** La distribution presents déjà un maximum net au voisinage de $\theta \approx 0^\circ$. Ce maximum ne provient pas principalement du cisaillement, qui reste faible dans ce régime, mais de l’effet de confinement géométrique près de la surface. Le mouvement brownien permet encore au bâtonnet d’explorer un intervalle d’angles relativement large, mais les grandes inclinaisons, proches de $\pm 90^\circ$, sont fortement réduites par l’interaction stérique avec la paroi. Les très faibles différences entre les bins voisins autour de $\theta = 0^\circ$ ne doivent pas être interprétées comme un déplacement physique significatif du maximum, mais comme des fluctuations statistiques liées à l’échantillonnage numérique.

* **Pour $\alpha = 2$ :** Le maximum de la distribution se décale vers des angles positifs, autour de $\theta_{\max} \approx 5.5^\circ$. Ce déplacement indique que le cisaillement commence à influencer plus nettement l’orientation du bâtonnet près de la surface. La distribution résulte alors de la combinaison de deux effets : la contrainte géométrique imposée par la paroi, qui tend à maintenir le bâtonnet presque parallèle à la surface, et le couple hydrodynamique dû au cisaillement, qui introduit une orientation préférentielle positive.

* **Pour $\alpha = 5$ :** Le maximum devient plus marqué et se déplace davantage vers les angles positifs, autour de $\theta_{\max} \approx 11.5^\circ$. Cela montre que l’effet hydrodynamique devient plus important lorsque $\alpha$ augmente. Cependant, la distribution reste concentrée dans une zone angulaire proche de $\theta = 0^\circ$, ce qui indique que l’effet de la surface demeure dominant dans cette région. La paroi limite fortement les orientations accessibles et empêche le bâtonnet d’adopter librement de grandes inclinaisons.

Les faibles probabilités observées près de $\theta = \pm 90^\circ$ sont cohérentes avec la physique du problème. Près de la surface, une orientation presque perpendiculaire à la paroi est très défavorable, car elle augmente fortement le risque de contact géométrique avec la paroi. Le bâtonnet passe donc très peu de temps dans ces orientations extrêmes.

---

> 💡 **Comparaison Physique Majeure (Volume vs Surface) :**
> En volume ($\xi > 0.5$), le régime à $\alpha = 0.5$ est dominé par l'isotropie brownienne (courbe quasi-uniforme). Près de la surface ($\xi \leq 0.5$), un pic d'orientation très net apparaît immédiatement à $\alpha = 0.5$. Cela démontre l'impact crucial du confinement : la paroi brise la symétrie rotationnelle du système en imposant un alignement géométrique du bâtonnet parallèlement à elle.
> 
> En conclusion, près de la surface, l’orientation du bâtonnet est contrôlée conjointement par le confinement géométrique et par le cisaillement hydrodynamique. À faible $\alpha$, la paroi impose principalement un alignement quasi parallèle à la surface. Lorsque $\alpha$ augmente, le cisaillement déplace progressivement l’orientation préférentielle vers des angles positifs. Les positions des maxima physiques sont approximativement $\theta_{\max} \approx 0^\circ$ pour $\alpha = 0.5$, $\theta_{\max} \approx 5.5^\circ$ pour $\alpha = 2$, et $\theta_{\max} \approx 11.5^\circ$ pour $\alpha = 5$.
