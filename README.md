# Quelques liens et notes pour aider sur ESP32-S3

## liens
produit: https://www.amazon.fr/dp/B0DJVYJH7Q?ref=ppx_yo2ov_dt_b_fed_asin_title
Wiki: https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.28
lib LVGL: https://github.com/lvgl/lvgl/tree/master

https://github.com/h1f1x/iot-esp32-touch


## NOTA

Avis sur Amazon source
```
https://www.amazon.fr/dp/B0CM68M8LR/ref=sspa_dk_detail_6?psc=1&pd_rd_i=B0CM68M8LR&pd_rd_w=9YX3k&content-id=amzn1.sym.bebca2a6-c9e4-4073-8fe8-a15bac2d53a9&pf_rd_p=bebca2a6-c9e4-4073-8fe8-a15bac2d53a9&pf_rd_r=E5D3QNHEY2NW36YRC3BS&pd_rd_wg=4ToLY&pd_rd_r=a7bec428-c927-445e-acc9-610593297227&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWxfdGhlbWF0aWM#customerReviews
---
Équipement de la carte :
- l'ESP32-S3R2, un processeur bicœur 32 bits à 240 MHz, avec 2 Mo de RAM intégrée, Wi-Fi 2,4 GHz, Bluetooth LE, 45 GPIO (6 exposés sur le câble), etc.
- antenne WiFi/BT intégrée - Flash externe de 16 Mo pour le firmware et le stockage (W25Q128JVSIQ) - Accéléromètres 3 axes IMU + gyroscopes 3 axes (QMI8658A) - UMI8658A Convertisseur ART vers USB et connecteur USB-C - Régulateur de tension 3,3 V 800 mA (ME1762C33M5G), puce de chargeur de batterie au lithium (ETA6096) et connecteur MX1.25, batterie externe rechargeable 3,7 V (à l'achat)

séparément)
- deux microrupteurs pour la réinitialisation et le démarrage
- connecteur de brochage pour les alimentations et 6 GPIO programmables (15,16,17,18,21,33), et câble de dérivation
- Écran LCD TFT de 1,28 pouces (32,4 mm) avec écran tactile capacitif (CST816D) Connecté à l'alimentation USB-C, l'écran TFT (diamètre 32,4 mm : celui d'une montre

connectée) s'allume et affiche une application de démonstration avec certains jauges (calendrier, commandes de saisie, images, etc.) et informations de référence ; elles sont bien définies et lumineuses et le rafraîchissement est très réactif (33 images par seconde). Lors de la réinitialisation, le démarrage est instantané : moins d'une demi-seconde et l'application est active.

Pour le programmer, vous pouvez utiliser l'IDE Arduino, VSCode avec PlatformIO ou d'autres outils et frameworks de développement ; comme malgré une bonne expérience, il m'a fallu un certain temps pour compiler les exemples, voici quelques conseils pour configurer l'environnement avec l'IDE Arduino, celui qui est le plus abordable : 1.
Installez le support ESP32 d'Espressif via le gestionnaire de cartes 2.
En tant que carte, vous pouvez sélectionner la carte « Module de développement ESP32S3 » et configurer la communication virtuelle USB pour le téléchargement ; de plus, dans le menu Outils, il est nécessaire de définir FlashSize=16 Mo et PSRAM=QSPI 3.
Pour l'affichage, le driver le plus utilisé est la bibliothèque TFT_ESPI, la dernière version 2.5.43 convient, mais il faut la configurer en éditant le fichier User_Setup_Select.h, en désactivant l'inclusion générique 'User_Setup.h' et en activant 'User_Setups/Setup302_WaveShare_ESP32S3_GC9A01.h' ; j'ai également dû ajouter une définition TOUCHCH _CS 9 pour la broche de l'écran tactile, sinon les exemples 4 ne seraient pas compilés.
Presque tous les exemples utilisent la bibliothèque graphique LVGL.io : j'ai utilisé la version 8.4 (pas la dernière) et il est nécessaire de créer le fichier lv_conf.h avec les paramètres dans le dossier de la bibliothèque (il est préférable de le copier à partir du fichier zip d'exemple) ; si vous souhaitez utiliser les démos, vous devez également copier le dossier lvgl/demos dans le chemin lvgl/src/demos. D'autres exemples utilisent également la bibliothèque LovyangFX.
5. L'écran tactile capacitif CST816S utilise l'interface I2C et il existe une bibliothèque simple à utiliser qui gère les principaux gestes (balayage vers le haut/le bas/la gauche/la droite, etc.) ; l'adresse I2C à définir est la valeur par défaut 0x15 6.
Enfin, pour utiliser l'IMU à 6 axes, vous pouvez prendre le code d'un exemple ou installer l'une des bibliothèques : FastIMU, Qmi8658C ou SensorLib.

Avantages :
- bien conçu et complet pour expérimenter l'ESP32 avec écrans LCD et tactiles
- puce puissante et hautement supportée : programmable avec Arduino, ESP-IDF, MicroPython, etc.
- Bonne définition, écran LCD lumineux et rapide

Inconvénients :
- Ni sur la carte d'achat, ni dans l'emballage, il ne contient de lien avec de la documentation et des exemples, il faut le rechercher sur le site Web du fabricant
- pas pour tout le monde : pour configurer et utiliser les bibliothèques graphiques, vous avez besoin d'une bonne quantité de expérience de développement avec Arduino et avec l'imprimante intégrée en général.. il y a un peu à étudier
 : elle n'est pas livrée avec un conteneur, mais si vous avez ou avez accès à une imprimante 3D, vous pouvez trouver quelque chose sur les sites de modèles 3D.
```
