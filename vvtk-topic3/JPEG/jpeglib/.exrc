if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <S-Tab> 
smap 	 i<BS>	
xmap 	 >gv
nmap 	 V>
noremap / :call SearchCompleteStart()/
nnoremap \q :QFix
nmap gx <Plug>NetrwBrowseX
nmap tc :tabclose
nmap tn :tabnew
nmap th :tabprev
nmap tl :tabnext
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetBrowseX(expand("<cWORD>"),0)
nmap <C-Tab> :tabnext
nnoremap <F12> :TlistToggle
nnoremap <F11> :NERDTree
nnoremap <F10> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
nnoremap <F9> :w | !gcc % && ./a.out
xmap <S-Tab> <gv
nmap <S-Tab> V<
imap 	 <Plug>Jumper
inoremap <expr>  omni#cpp#maycomplete#Complete()
imap  =CtrlXPP()
inoremap <expr> . omni#cpp#maycomplete#Dot()
inoremap <expr> : omni#cpp#maycomplete#Scope()
inoremap <expr> > omni#cpp#maycomplete#Arrow()
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=2
set backup
set completeopt=preview,menuone
set cscopeprg=/usr/bin/cscope
set cscopetag
set cscopeverbose
set errorformat=%f:%l:\ %m
set expandtab
set fileencodings=big5,utf-8,,euc-jp,gbk,euc-kr,utf-bom,iso8859-1
set formatoptions=tcql
set helplang=en
set history=50
set hlsearch
set incsearch
set laststatus=2
set makeprg=make\ %<
set omnifunc=omni#cpp#complete#Main
set ruler
set runtimepath=~/.vim,/usr/share/vim/vimfiles,/usr/share/vim/vim70,/usr/share/vim/vimfiles/after,~/.vim/after,~/.vim/textmateOnly,~/.vim/textmateOnly/after
set shiftwidth=4
set showcmd
set showmatch
set softtabstop=4
set statusline=%<%f\ %m%=\ %h%r\ %-19([%p%%]\ %3l,%02c%03V%)%y
set tabstop=4
set termencoding=utf-8
set wildmenu
" vim: set ft=vim :
