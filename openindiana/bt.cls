% !TeX root = optimize-unix.tex
% 'bt' LaTeX class

% ------------ identification --------------
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{bt}[2017/05/12 Bernard TATIN]


% ------------ required packages ------------
\RequirePackage{gfsbodoni}
\RequirePackage[utf8]{inputenc}
\RequirePackage[francais]{babel}
\RequirePackage[T1]{fontenc}

\RequirePackage{fancyhdr} 
% ------------ journal options --------------
\newif\ifbtjournal        	 \btjournalfalse
\newif\ifbtbook         	\btbookfalse
\newif\ifbtsansserif      \btsansseriffalse
\newif\ifbtserif         	\btseriffalse

\newcommand{\bt@columnmode}{}
\newlength\bt@pointsize
\newif\ifwithpartalpha	\withpartalphafalse


\DeclareOption{journal}{%
   \btjournaltrue %
   \btsansseriftrue
   \btseriffalse
   \withpartalphatrue
   \bt@pointsize=9pt
}

\DeclareOption{book}{%
   \btbooktrue %
   \btseriftrue
   \btsansseriffalse
   \withpartalphatrue
   \bt@pointsize=12pt
}

\DeclareOption{sserif}{
	\btsansseriftrue
	\btseriffalse
}
\DeclareOption{serif}{
	\btseriftrue
	\btsansseriffalse
}


\DeclareOption{9pt}{%
   \bt@pointsize=9pt
}
\DeclareOption{10pt}{%
   \bt@pointsize=10pt
}
\DeclareOption{11pt}{%
   \bt@pointsize=11pt
}
\DeclareOption{12pt}{%
   \bt@pointsize=12pt
}

% \DeclareOption{openbib}{%
   % \AtEndOfPackage{%
   % \renewcommand\@openbib@code{%
      % \advance\leftmargin\bibindent
      % \itemindent -\bibindent
      % \listparindent \itemindent
      % \parsep \z@
   % }
   % \renewcommand\newblock{\par}}%
% }


% ------------ base classe -----------------
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions
\ifdim\bt@pointsize>11pt
   \PassOptionsToClass{12pt}{article}
\else
	\ifdim\bt@pointsize=11pt
   		\PassOptionsToClass{11pt}{article}
	\else
		\ifdim\bt@pointsize=10pt
	   		\PassOptionsToClass{10pt}{article}
		\fi
	\fi
\fi

\LoadClass{article}
%% these packages must be AFTER the class is loaded !!
%% needed by the list of listings
\RequirePackage{listings}
\RequirePackage{caption}

\ifwithpartalpha
	\RequirePackage{chngcntr}
\fi
\ifbtsansserif
	\renewcommand{\rmdefault}{phv} % Switch to Helvetica !
\fi
% \ifbtserif
%	\renewcommand{\sfdefault}{phv} % Switch to Helvetica !
%\fi

% ------------ abstract configuration ------
\newcommand{\bt@abstxt}{}
\let\origabstract\abstract
\let\endorigabstract\endabstract
\renewcommand{\abstract}[1]{\renewcommand{\bt@abstxt}{#1}}

\newlength{\abstxtspace}
\setlength{\abstxtspace}{0.20in}

\newlength{\titlespace}
\setlength{\titlespace}{0.25in}

\newlength{\teaserspace}
\setlength{\teaserspace}{0.0in}


\newcommand{\authorfootertext}{}
\newcommand{\authorfooter}[1]{\renewcommand{\authorfootertext}{{\em#1}}}

\renewcommand{\figurename}{Fig.}

\setlength\paperheight {297mm}%
\setlength\paperwidth {210mm}

\setlength{\hoffset}{1.0in}
\setlength{\textheight}{9.625in}
\setlength{\topmargin}{-0.625in}
\setlength{\headheight}{0.0625in}
\setlength{\headsep}{0.250in}
\setlength{\footskip}{0.25in}
\flushbottom
\setlength{\textwidth}{5.325in}
\setlength{\columnsep}{0.17in}
\setlength{\marginparwidth}{65em}
%\newlength{\captionmargin}
%\setlength{\captionmargin}{0in}

\setlength{\evensidemargin}{-0.6875in} %1in-0.3125
\setlength{\oddsidemargin}{-.58in} %1in-0.4375

\renewcommand{\ps@plain}%
   {%
      \renewcommand{\@oddhead}{\hfil\textit{\THETITLE}\hfil}%
      \renewcommand{\@oddfoot}{\hfil\textrm{\thepage}\hfil}%
      \renewcommand{\@evenhead}{\@oddhead}%
      \renewcommand{\@evenfoot}{\@oddfoot}%
   }

\pagestyle{plain}

\newcommand{\bt@setninepoint}{%
   \renewcommand\normalsize{%
       \@setfontsize\normalsize\@ixpt\@xpt
       \abovedisplayskip 9\p@ \@plus2\p@ \@minus4\p@
       \abovedisplayshortskip \z@ \@plus3\p@
       \belowdisplayshortskip 6\p@ \@plus3\p@ \@minus3\p@
       \belowdisplayskip \abovedisplayskip
       \let\@listi\@listI}
   \renewcommand\small{%
       \@setfontsize\small\@viipt\@ixpt
       \abovedisplayskip 8.5\p@ \@plus3\p@ \@minus4\p@
       \abovedisplayshortskip \z@ \@plus2\p@
       \belowdisplayshortskip 4\p@ \@plus2\p@ \@minus2\p@
       \def\@listi{\leftmargin\leftmargini
                   \topsep 4\p@ \@plus2\p@ \@minus2\p@
                   \parsep 2\p@ \@plus\p@ \@minus\p@
                   \itemsep \parsep}%
       \belowdisplayskip \abovedisplayskip}
   \renewcommand\footnotesize{%
       \@setfontsize\footnotesize\@viiipt{9.5}%
       \abovedisplayskip 6\p@ \@plus2\p@ \@minus4\p@
       \abovedisplayshortskip \z@ \@plus\p@
       \belowdisplayshortskip 3\p@ \@plus\p@ \@minus2\p@
       \def\@listi{\leftmargin\leftmargini
                   \topsep 3\p@ \@plus\p@ \@minus\p@
                   \parsep 2\p@ \@plus\p@ \@minus\p@
                   \itemsep \parsep}%
       \belowdisplayskip \abovedisplayskip}
   \renewcommand\scriptsize{\@setfontsize\scriptsize\@viiipt{9.5}}
   \renewcommand\tiny{\@setfontsize\tiny\@vpt\@vipt}
   \renewcommand\large{\@setfontsize\large\@xpt\@xiipt}
   \renewcommand\Large{\@setfontsize\Large\@xiipt{14}}
   \renewcommand\LARGE{\@setfontsize\LARGE\@xivpt{18}}
   \renewcommand\huge{\@setfontsize\huge\@xviipt{22}}
   \renewcommand\Huge{\@setfontsize\Huge\@xxpt{25}}
   \selectfont
}
\ifdim\bt@pointsize<10pt
   \bt@setninepoint
\fi

\newcommand{\bt@sectionfont}{}
\newcommand{\sectionfont}[1]{\renewcommand{\bt@sectionfont}{#1}}

% \renewcommand\part{\@startsection{part}{0}{\z@}%
% 	{-2ex \@plus -1ex \@minus -.2ex}%
%          {0.8ex \@plus .2ex}%
% 	{%% \secdef
% 	\reset@font\Large\sffamily\bfseries\scshape
% 	\bt@sectionfont}
% }

\renewcommand\section{\@startsection{section}{1}{2em}%
               {-2ex \@plus -1ex \@minus -.2ex}%
               {0.8ex \@plus .2ex}%
               {\reset@font\normalsize\sffamily\bfseries\scshape\bt@sectionfont}}
\renewcommand\subsection{\@startsection{subsection}{2}{\z@}%
               {-1.8ex\@plus -1ex \@minus -.2ex}%
               {0.8ex \@plus .2ex}%
               {\reset@font\normalsize\sffamily\bfseries\bt@sectionfont - }}
\renewcommand\subsubsection{\@startsection{subsubsection}{3}{\z@}%
               {-1.8ex\@plus -1ex \@minus -.2ex}%
               {0.8ex \@plus .2ex}%
               {\reset@font\sffamily\normalsize\bt@sectionfont}}

\renewcommand\paragraph{\@startsection{paragraph}{4}{1em}%
               {1ex \@plus 1ex \@minus.2ex}%
               {-1em}%
               {\reset@font\normalsize\sffamily\hsize 5.5in\bt@sectionfont}}
\renewcommand\subparagraph{\@startsection{subparagraph}{5}{\parindent}%
               {3.25ex \@plus1ex \@minus .2ex}%
               {-1em}%
               {\reset@font\normalsize\sffamily\bfseries\bt@sectionfont}}


%% \ifwithpartalpha
	%\renewcommand{\thepart}{\emph{\alph{part}}}
%	\counterwithin{section}{part}
	%% \renewcommand{\thesection}{\thepart . \arabic{section}}
%% \fi

%\makeatletter
%% \def\@seccntformat#1{\csname the#1\endcsname.\ }
%\makeatother

\newcommand{\bt@indexterms}{}
\newcommand{\CCScatlist}[1]{\renewcommand{\bt@indexterms}{#1}}

\newcommand{\CCScat}[4]{%
    #1 [#2]%
    \ifx#3\bt@empty \else : #3\fi%
    \ifx#4\bt@empty \else ---#4\fi%
}

\let\bt@origmaketitle\maketitle
\let\bt@origand\and

\renewcommand{\footnoterule}{%
   \kern-3pt
   \leftline{\hskip1in\vbox{\hrule width 0.45\columnwidth}\hfil}
}

% ------------ title --------------
% save current title to use it in page header
\def\title#1{\gdef\@title{#1}\gdef\THETITLE{#1}}

\newcommand{\linediamond}{
	\centering
	\includegraphics{diamondrule.eps}
	\par%
}

\renewcommand{\@maketitle}{%
	\begin{center}%
		\sffamily
		{%
		   \huge\bfseries%
	      	   \bt@sectionfont%
	      	   \@title
	      	   \par
		}%
		\large\bt@sectionfont
		\vspace{14pt}%
		\begin{tabular}[t]{c}%
			\@author
		\end{tabular}\par%
		\linediamond
		{%
			\scriptsize
			\ifx\bt@abstxt\bt@empty \else%
				\leftskip = 1.33in \rightskip = \leftskip%
				\begingroup%
					{\bfseries Résumé}---\bt@abstxt%
				\endgroup\par%
				\linediamond
			\fi%
			\begin{quote}
				\tableofcontents
				\lstlistoflistings
				\listoffigures
			\end{quote}
			\linediamond
			%\listoffigures
			%\listoftables
			%\linediamond
		}
	\end{center}%
}



%% pour les annexes
\renewcommand\appendix{\par
   \setcounter{section}{0}%
   \setcounter{subsection}{0}%
   \gdef\thesection{\@Alph\c@section}
}

%% \setlength{\parindent}{2in}
%\setlength{\textwidth}{5.525in}
%\setlength{\columnsep}{0.17in}
%\setlength{\marginparwidth}{45em}
%\newlength{\captionmargin}
%\setlength{\captionmargin}{0in}

%\setlength\paperheight {297mm}%
%\setlength\paperwidth {210mm}
%\setlength{\evensidemargin}{-0.6875in} %1in-0.3125
%\setlength{\oddsidemargin}{-.58in} %1in-0.4375
% End of file 'bt.cls'.
