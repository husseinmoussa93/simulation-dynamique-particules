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
