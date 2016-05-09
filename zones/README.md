# les zones de Solaris

La procédure pour créer ma première zone est la suivante :

```bash
# création de l'espace disque de la zone
$ sudo zfs create rpool/znginx
# création de la zone
$ sudo zonecfg -z znginx
Password: 
Use 'create' to begin configuring a new zone.
zonecfg:znginx> create
create: Using system default template 'SYSdefault'
zonecfg:znginx> set zonepath=/rpool/znginx
zonecfg:znginx> set autoboot=true
zonecfg:znginx> set bootargs="-m verbose"
zonecfg:znginx> verify
zonecfg:znginx> commit
zonecfg:znginx> exit
# vérification de la bonne création de la zone
$ sudo zoneadm list -icv
  ID NAME             STATUS      PATH                         BRAND      IP    
   0 global           running     /                            solaris    shared
   - znginx           configured  /rpool/znginx                solaris    excl 
# installation de la zone
$ sudo zoneadm -z znginx install
```

