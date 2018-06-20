# Ana 

```
          _____                    _____                    _____          
         /\    \                  /\    \                  /\    \         
        /::\    \                /::\____\                /::\    \        
       /::::\    \              /::::|   |               /::::\    \       
      /::::::\    \            /:::::|   |              /::::::\    \      
     /:::/\:::\    \          /::::::|   |             /:::/\:::\    \     
    /:::/__\:::\    \        /:::/|::|   |            /:::/__\:::\    \    
   /::::\   \:::\    \      /:::/ |::|   |           /::::\   \:::\    \   
  /::::::\   \:::\    \    /:::/  |::|   | _____    /::::::\   \:::\    \  
 /:::/\:::\   \:::\    \  /:::/   |::|   |/\    \  /:::/\:::\   \:::\    \ 
/:::/  \:::\   \:::\____\/:: /    |::|   /::\____\/:::/  \:::\   \:::\____\
\::/    \:::\  /:::/    /\::/    /|::|  /:::/    /\::/    \:::\  /:::/    /
 \/____/ \:::\/:::/    /  \/____/ |::| /:::/    /  \/____/ \:::\/:::/    / 
          \::::::/    /           |::|/:::/    /            \::::::/    /  
           \::::/    /            |::::::/    /              \::::/    /   
           /:::/    /             |:::::/    /               /:::/    /    
          /:::/    /              |::::/    /               /:::/    /     
         /:::/    /               /:::/    /               /:::/    /      
        /:::/    /               /:::/    /               /:::/    /       
        \::/    /                \::/    /                \::/    /        
         \/____/                  \/____/                  \/____/         
                                                                           
```

This is the production repository for for Ana ('ahhn'-'ahh') a general<sup>1</sup> and programmable analysis tool for event reconstruction data using ROOT as a back end. The devolpment repository is private and releases will come upstream from that.

<sup>1</sup>Ana is general and can be 'hacked' for practically any data analysis, however this project does have an emphasis on reconstruction analysis for [CLAS12 @ JLab](https://www.jlab.org/Hall-B/clas12-web/ "CLAS12").

# Installation

ROOT needs to be installed to use Ana. For help, perhaps this [Gist](https://gist.github.com/smarky7CD/928aedbb873d97e23a3b4fc2fb202311 "ROOT Install Guide") I wrote detailing installation on Ubuntu 18.04 will prove useful. Moreover, the dependencies listed in that document are the same for Ana. So read that guide for those as well.

```
git clone --recurse-submodules https://github.com/smarky7CD/ana

cd ana

chmod +x install.sh

./install.sh
```

# Using Ana

```
./ana [name-of-project] [full-path-to-head-of-chain] [full-path-to-analysis-directory] [Tree-name*]
   
*Tree name only needs to be provided if feeding in ROOT files, otherwise it will be know due to conversion.
```

Read [analysis](https://github.com/smarky7CD/ana/blob/master/docs/analysis.md "About Analysis") and [data](https://github.com/smarky7CD/ana/blob/master/docs/data.md "About Data") docs to properly get familiar with using Ana.

# Releases

* **v0.1 alpha**: 06-20-2018 
