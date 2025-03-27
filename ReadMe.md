# Stratégie pour éviter les conflits

Nous étions une petite équipe comprenant deux programmeurs donc nous avons mis en place une communication solide. Lors des quelques conflits qui sont survenus, nous avons échangé pour déterminer qui disposait de la version la plus aboutie d’un *blueprint* ou d’un script C++, par exemple. Les programmeurs étaient également les seuls à utiliser **Git** afin de minimiser au maximum les conflits. Une seule *game designeuse* a eu besoin de cloner le projet ; elle était alors accompagnée par un programmeur si nécessaire.

De même, il y a eu une séparation distincte des tâches de programmation, pour éviter d'écraser le travail de l’autre. Nous avons aussi tenté au mieux de travailler chacun sur un *level test* distinct. À la fin de chaque journée, un *push* était fait, et nous vérifiions systématiquement l’absence de conflits. En début de journée un pull était fait et les conflits, si il y en avait, étaient réglés manuellement après discussion.

---

# Historique lisible

Pour avoir un historique lisible, nous avons encouragé entre nous l’utilisation de `git revert` à la place de `git commit --amend`. Nous avons tenté d'avoir des messages de *commit* les plus descriptifs et évocateurs possible des changements effectués, même si, au fil du temps, le niveau de rigueur a quelque peu varié. On aurait pu faire usage de rebase interactif pour améliorer la lisibilité d'ensemble en effaçant les messages de commits peu indicatif, par exemple.

---

# Git Workflow

Nous avons opté pour la simplicité dans le but d’être plus efficaces. Nous avions la branche `master` où se déroulait la majorité du développement, ainsi qu'une branche `IA` dédiée pendant un temps aux *features* liées à l’intelligence artificielle. Nous avions également prévu une branche de **fallback** (branche de secours), qui servait de point de retour stable en cas de problème.

Dans l’ensemble, nous avons d’abord mis en place un *workflow* basé sur les *features*, avant de rapidement basculer vers un *workflow* centralisé autour d’une seule branche `main`, après avoir constaté que la communication dans l'équipe était fluide. Étant seulement deux développeurs, cela réduisait fortement le risque de conflit.

Un .gitignore complet pour UE a été utilisé. Cela permet de faire en sorte de ne pas polluer notre repository. Une *pipeline* d’intégration et de déploiement continus (CI/CD) via GitHub a été envisagée pour automatiser les *builds* et gagner du temps. Mais après étude de la question, et compte tenu de notre manque de familiarité avec ces outils, cela a été abandonné afin de rester dans notre ligne directrice : la simplicité, ce qui nous a permis de grandement gagner du temps.

---

# Emploi de LFS

Nous n’avons pas utilisé **Git LFS** car nous étions confiants que nos *assets* ne dépasseraient pas la taille maximale autorisée par Git, notre projet étant de petite *scale* et se voulant optimisé.

Cependant, un *asset* provenant de notre équipe artistique a effectivement dépassé cette limite. **LFS** a alors été envisagé, mais en raison d'une expérience précédente (où l’un d’entre nous avait atteint le quota du plan gratuit, ce qui a nécessité une suppression laborieuse de LFS avec git lfs migrate import), nous avons préféré que l’*asset* soit revu et allégé par les artistes.

---

# Alternative

L’option d’utiliser **Diversion**, un outil de *version control* alternatif conçu spécifiquement pour Unreal Engine et les fichiers `.uasset`, a été étudiée. Après considération, cette solution n’a pas été retenue en raison de notre manque de familiarité avec l’outil, ce qui aurait pu entraîner une perte de temps inutile.

---

# Leçons apprises

Lors de la première semaine intensive, un conflit important a entraîné la perte de modifications sur un *level*. Cela s’est produit parce que, sous la pression de la deadline, les mécanismes de prudence que nous avions mis en place n'ont pas été respectés.

Cet incident nous a appris l’importance de ralentir le rythme des *push*, même en période de stress, et de rester rigoureux quant aux bonnes pratiques établies. Une meilleure discipline collective à ce niveau nous a permis d’éviter que ce genre de situation ne se reproduise par la suite.

---

# Conclusion

En résumé, notre approche Git, bien qu’adaptée à notre contexte de petite équipe et à notre besoin de **rapidité**, s’est appuyée sur des principes solides : communication constante, séparation des responsabilités, rigueur sur les commits, et adaptation progressive du *workflow*. Nous avons su tirer des leçons de nos erreurs pour construire un plan de production stable, fluide et collaboratif.

---

# Bonus

[Voir l’historique Git (git-graph.txt)](./git-graph.txt)