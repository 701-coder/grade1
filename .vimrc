set nocompatible
set encoding=utf-8
set fileencoding=utf-8

se nu ai hls et ru ic is sc cul
se re=1 ts=4 sts=4 sw=4 ls=2 mouse=a
syntax on
hi cursorline cterm=none ctermbg=89
set bg=dark
set ar fdm=manual nu ts=2 sw=2 ai rnu
sy on

function InitLatex()
    map <F9> :w<bar>!~/xelatex.sh<CR>
    inoremap <F9> <Esc>:w<bar>!~/xelatex.sh<CR>
endfunction

function InitCpp()
    map <F9> :w<bar>!~/g++.sh "%"<CR>
    inoremap <F9> <Esc>:w<bar>!~/g++.sh "%"<CR>
endfunction

function InitHtml()
    map <F9> :w<bar>!~/html.sh "%"<CR>
    inoremap <F9> <Esc>:w<bar>!~/html.sh "%"<CR>
endfunction

function InitC()
    map <F9> :w<bar>!~/gcc.sh "%"<CR>
    inoremap <F9> <Esc>:w<bar>!~/gcc.sh "%"<CR>
endfunction

au Bufenter *.tex call InitLatex()
au Bufenter *.cpp call InitCpp()
au Bufenter *.html call InitHtml()
au Bufenter *.c call InitC()
