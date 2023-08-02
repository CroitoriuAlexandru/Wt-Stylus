
// ${<if-register>} ${template.name class=""} ${</if-register>}
// ${template.name class=""}




// spacing regexp
// std::regex padding_regexp = std::regex("p[x,y,t,r,b,l]?-(?:96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
// std::regex margin_regexp =  std::regex("-?m[x,y,t,r,b,l]?-(?:auto|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
// std::regex space_regexp = std::regex("space-[x|y]?-(?:reverse|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");


// sizing regexp
// std::regex width_regexp = std::regex("w-(?:fit|max|min|screen|full|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");
// std::regex minWidth_regex = std::regex("min-w-(?:0|full|min|max|fit|\\[[\\S]*\\])");
// std::regex maxWidth_regex = std::regex("max-w-(?:0|none|xs|sm|md|ls|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|full|min|max|fit|prose|screen-sm|screen-md|screen-lg|screen-xl|screen-2x|\\[[\\S]*\\])");

// std::regex height_regexp = std::regex("(?:\\s|^)h-(?:full|screen|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");

namespace asdasd{
//--------------------------------------------------------------

// Padding classes
// p-px p-0 p-0.5 p-1 p-1.5 p-2 p-2.5 p-3 p-3.5 p-4 p-5 p-6 p-6 p-7 p-8 p-8 p-9 p-10 p-11 p-12 p-14 p-16 p-20 p-24 p-28 p-32 p-36 p-40 p-44 p-48 p-52 p-56 p-64 p-72 p-80 p-96 p-[10px]

// px-px px-0 px-0.5 px-1 px-1.5 px-2 px-2.5 px-3 px-3.5 px-4 px-5 px-6 px-6 px-7 px-8 px-8 px-9 px-10 px-11 px-12 px-14 px-16 px-20 px-24 px-28 px-32 px-36 
// px-40 px-44 px-48 px-52 px-56 px-64 px-72 px-80 px-96 px-[10px]

// py-px py-0 py-0.5 py-1 py-1.5 py-2 py-2.5 py-3 py-3.5 py-4 py-5 py-6 py-6 py-7 py-8 py-8 py-9 py-10 py-11 py-12 py-14 py-16 py-20 py-24 py-28 py-32 py-36 
// py-40 py-44 py-48 py-52 py-56 py-64 py-72 py-80 py-96 py-[10px]

// pt-px pt-0 pt-0.5 pt-1 pt-1.5 pt-2 pt-2.5 pt-3 pt-3.5 pt-4 pt-5 pt-6 pt-6 pt-7 pt-8 pt-8 pt-9 pt-10 pt-11 pt-12 pt-14 pt-16 pt-20 pt-24 pt-28 pt-32 pt-36 
// pt-40 pt-44 pt-48 pt-52 pt-56 pt-64 pt-72 pt-80 pt-96 pt-[10px]

// pr-px pr-0 pr-0.5 pr-1 pr-1.5 pr-2 pr-2.5 pr-3 pr-3.5 pr-4 pr-5 pr-6 pr-6 pr-7 pr-8 pr-8 pr-9 pr-10 pr-11 pr-12 pr-14 pr-16 pr-20 pr-24 pr-28 pr-32 pr-36 
// pr-40 pr-44 pr-48 pr-52 pr-56 pr-64 pr-72 pr-80 pr-96 pr-[10px]

// pb-px pb-0 pb-0.5 pb-1 pb-1.5 pb-2 pb-2.5 pb-3 pb-3.5 pb-4 pb-5 pb-6 pb-6 pb-7 pb-8 pb-8 pb-9 pb-10 pb-11 pb-12 pb-14 pb-16 pb-20 pb-24 pb-28 pb-32 pb-36 
// pb-40 pb-44 pb-48 pb-52 pb-56 pb-64 pb-72 pb-80 pb-96 pb-[10px]

// pl-px pl-0 pl-0.5 pl-1 pl-1.5 pl-2 pl-2.5 pl-3 pl-3.5 pl-4 pl-5 pl-6 pl-6 pl-7 pl-8 pl-8 pl-9 pl-10 pl-11 pl-12 pl-14 pl-16 pl-20 pl-24 pl-28 pl-32 pl-36 
// pl-40 pl-44 pl-48 pl-52 pl-56 pl-64 pl-72 pl-80 pl-96 pl-[10px]

//--------------------------------------------------------------

// Margin Classes
// m-auto m-px m-0 m-0.5 m-1 m-1.5 m-2 m-2.5 m-3 m-3.5 m-4 m-5 m-6 m-6 m-7 m-8 m-8 m-9 m-10 m-11 m-12 m-14 m-16 m-20 m-24 m-28 m-32 m-36 m-40 m-44 m-48 m-52 m-56 m-64 m-72 m-80 m-96 m-[10px]
// -m-px -m-0 -m-0.5 -m-1 -m-1.5 -m-2 -m-2.5 -m-3 -m-3.5 -m-4 -m-5 -m-6 -m-6 -m-7 -m-8 -m-8 -m-9 -m-10 -m-11 -m-12 -m-14 -m-16 -m-20 -m-24 -m-28 -m-32 -m-36 -m-40 -m-44 -m-48 -m-52 -m-56 -m-64 -m-72 -m-80 -m-96 m-[-10px]

// mx-auto mx-px mx-0 mx-0.5 mx-1 mx-1.5 mx-2 mx-2.5 mx-3 mx-3.5 mx-4 mx-5 mx-6 mx-6 mx-7 mx-8 mx-8 mx-9 mx-10 mx-11 mx-12 mx-14 mx-16 mx-20 mx-24 mx-28 mx-32 mx-36 mx-40 mx-44 mx-48 mx-52 mx-56 mx-64 mx-72 mx-80 mx-96 mx-[10px]
// -mx-px -mx-0 -mx-0.5 -mx-1 -mx-1.5 -mx-2 -mx-2.5 -mx-3 -mx-3.5 -mx-4 -mx-5 -mx-6 -mx-6 -mx-7 -mx-8 -mx-8 -mx-9 -mx-10 -mx-11 -mx-12 -mx-14 -mx-16 -mx-20 -mx-24 -mx-28 -mx-32 -mx-36 -mx-40 -mx-44 -mx-48 -mx-52 -mx-56 -mx-64 -mx-72 -mx-80 -mx-96 mx-[-10px]

// my-auto my-px my-0 my-0.5 my-1 my-1.5 my-2 my-2.5 my-3 my-3.5 my-4 my-5 my-6 my-6 my-7 my-8 my-8 my-9 my-10 my-11 my-12 my-14 my-16 my-20 my-24 my-28 my-32 my-36 my-40 my-44 my-48 my-52 my-56 my-64 my-72 my-80 my-96 my-[10px]
// -my-px -my-0 -my-0.5 -my-1 -my-1.5 -my-2 -my-2.5 -my-3 -my-3.5 -my-4 -my-5 -my-6 -my-6 -my-7 -my-8 -my-8 -my-9 -my-10 -my-11 -my-12 -my-14 -my-16 -my-20 -my-24 -my-28 -my-32 -my-36 -my-40 -my-44 -my-48 -my-52 -my-56 -my-64 -my-72 -my-80 -my-96 my-[-10px]

// mt-auto mt-px mt-0 mt-0.5 mt-1 mt-1.5 mt-2 mt-2.5 mt-3 mt-3.5 mt-4 mt-5 mt-6 mt-6 mt-7 mt-8 mt-8 mt-9 mt-10 mt-11 mt-12 mt-14 mt-16 mt-20 mt-24 mt-28 mt-32 mt-36 mt-40 mt-44 mt-48 mt-52 mt-56 mt-64 mt-72 mt-80 mt-96 mt-[10px]
// -mt-px -mt-0 -mt-0.5 -mt-1 -mt-1.5 -mt-2 -mt-2.5 -mt-3 -mt-3.5 -mt-4 -mt-5 -mt-6 -mt-6 -mt-7 -mt-8 -mt-8 -mt-9 -mt-10 -mt-11 -mt-12 -mt-14 -mt-16 -mt-20 -mt-24 -mt-28 -mt-32 -mt-36 -mt-40 -mt-44 -mt-48 -mt-52 -mt-56 -mt-64 -mt-72 -mt-80 -mt-96 mt-[-10px]

// mr-auto mr-px mr-0 mr-0.5 mr-1 mr-1.5 mr-2 mr-2.5 mr-3 mr-3.5 mr-4 mr-5 mr-6 mr-6 mr-7 mr-8 mr-8 mr-9 mr-10 mr-11 mr-12 mr-14 mr-16 mr-20 mr-24 mr-28 mr-32 mr-36 mr-40 mr-44 mr-48 mr-52 mr-56 mr-64 mr-72 mr-80 mr-96 mr-[10px]
// -mr-px -mr-0 -mr-0.5 -mr-1 -mr-1.5 -mr-2 -mr-2.5 -mr-3 -mr-3.5 -mr-4 -mr-5 -mr-6 -mr-6 -mr-7 -mr-8 -mr-8 -mr-9 -mr-10 -mr-11 -mr-12 -mr-14 -mr-16 -mr-20 -mr-24 -mr-28 -mr-32 -mr-36 -mr-40 -mr-44 -mr-48 -mr-52 -mr-56 -mr-64 -mr-72 -mr-80 -mr-96 mr-[-10px]

// mb-auto mb-px mb-0 mb-0.5 mb-1 mb-1.5 mb-2 mb-2.5 mb-3 mb-3.5 mb-4 mb-5 mb-6 mb-6 mb-7 mb-8 mb-8 mb-9 mb-10 mb-11 mb-12 mb-14 mb-16 mb-20 mb-24 mb-28 mb-32 mb-36 mb-40 mb-44 mb-48 mb-52 mb-56 mb-64 mb-72 mb-80 mb-96 mb-[10px]
// -mb-px -mb-0 -mb-0.5 -mb-1 -mb-1.5 -mb-2 -mb-2.5 -mb-3 -mb-3.5 -mb-4 -mb-5 -mb-6 -mb-6 -mb-7 -mb-8 -mb-8 -mb-9 -mb-10 -mb-11 -mb-12 -mb-14 -mb-16 -mb-20 -mb-24 -mb-28 -mb-32 -mb-36 -mb-40 -mb-44 -mb-48 -mb-52 -mb-56 -mb-64 -mb-72 -mb-80 -mb-96 mb-[-10px]

// ml-auto ml-px ml-0 ml-0.5 ml-1 ml-1.5 ml-2 ml-2.5 ml-3 ml-3.5 ml-4 ml-5 ml-6 ml-6 ml-7 ml-8 ml-8 ml-9 ml-10 ml-11 ml-12 ml-14 ml-16 ml-20 ml-24 ml-28 ml-32 ml-36 ml-40 ml-44 ml-48 ml-52 ml-56 ml-64 ml-72 ml-80 ml-96 ml-[10px]
// -ml-px -ml-0 -ml-0.5 -ml-1 -ml-1.5 -ml-2 -ml-2.5 -ml-3 -ml-3.5 -ml-4 -ml-5 -ml-6 -ml-6 -ml-7 -ml-8 -ml-8 -ml-9 -ml-10 -ml-11 -ml-12 -ml-14 -ml-16 -ml-20 -ml-24 -ml-28 -ml-32 -ml-36 -ml-40 -ml-44 -ml-48 -ml-52 -ml-56 -ml-64 -ml-72 -ml-80 -ml-96 ml-[-10px]

// Space Classes
// space-x-0 space-x-0.5 space-x-1 space-x-1.5 space-x-2 space-x-2.5 space-x-3 space-x-3.5 space-x-4 space-x-5 space-x-6 space-x-7 space-x-8 space-x-9 space-x-10 space-x-11 space-x-12 space-x-14 space-x-16 space-x-20 space-x-24 space-x-28 space-x-32 space-x-36 space-x-40 space-x-44 space-x-48 space-x-52 space-x-56 space-x-60 space-x-64 space-x-72 space-x-80 space-x-96 space-x-px space-x-reverse space-x-[30px]

// space-y-0 space-y-0.5 space-y-1 space-y-1.5 space-y-2 space-y-2.5 space-y-3 space-y-3.5 space-y-4 space-y-5 space-y-6 space-y-7 space-y-8 space-y-9 space-y-10 space-y-11 space-y-12 space-y-14 space-y-16 space-y-20 space-y-24 space-y-28 space-y-32 space-y-36 space-y-40 space-y-44 space-y-48 space-y-52 space-y-56 space-y-60 space-y-64 space-y-72 space-y-80 space-y-96 space-y-px space-y-reverse space-y-[30px]

}

namespace sdf {

// width classes
// w-0 w-px w-0.5 w-1 w-1.5 w-2 w-2.5 w-3 w-3.5 w-4 w-5 w-6 w-7 w-8 w-9 w-10 w-11 w-12 w-14 w-16 w-20 w-24 w-28 w-32 w-36 w-40 w-44 w-48 w-52 w-56 w-60 w-64 w-72 w-80 w-96 w-auto w-1/2 w-1/3 w-2/3 w-1/4 w-2/4 w-3/4 w-1/5 w-2/5 w-3/5 w-4/5 w-1/6 w-2/6 w-3/6 w-4/6 w-5/6 w-1/12 w-2/12 w-3/12 w-4/12 w-5/12 w-6/12 w-7/12 w-8/12 w-9/12 w-10/12 w-11/12 w-full w-screen w-min w-max w-fit w-[20px]

// min width classes
// min-w-0 min-w-full min-w-min min-w-max min-w-fit min-w-[30px]

// max width classes
// max-w-0 max-w-none max-w-xs max-w-sm max-w-md max-w-lg max-w-xl max-w-2xl max-w-3xl max-w-4xl max-w-5xl max-w-6xl max-w-7xl max-w-full max-w-min max-w-max max-w-fit max-w-prose max-w-screen-sm	max-w-screen-md max-w-screen-lg max-w-screen-xl max-w-screen-2x max-w-[50px]

// height classes
// h-0 h-px h-0.5 h-1 h-1.5 h-2 h-2.5 h-3 h-3.5 h-4 h-5 h-6 h-7 h-8 h-9 h-10 h-11 h-12 h-14 h-16 h-20 h-24 h-28 h-32 h-36 h-40 h-44 h-48 h-52 h-56 h-60 h-64 h-72 h-80 h-96 h-auto h-1/2 h-1/3 h-2/3 h-1/4 h-2/4 h-3/4 h-1/5 h-2/5 h-3/5 h-4/5 h-1/6 h-2/6 h-3/6 h-4/6 h-5/6 h-1/12 h-2/12 h-3/12 h-4/12 h-5/12 h-6/12 h-7/12 h-8/12 h-9/12 h-10/12 h-11/12 h-full h-screen h-min h-max h-fit h-[20px]

// min height classes
// min-h-0	min-h-full min-h-screen min-h-min min-h-max min-h-fit min-h-[30px]

// max height classes
// max-h-0 max-h-px max-h-0.5 max-h-1 max-h-1.5 max-h-2 max-h-2.5 max-h-3 max-h-3.5 max-h-4 max-h-5 max-h-6 max-h-7 max-h-8 max-h-9 max-h-10 max-h-11 max-h-12 max-h-14 max-h-16 max-h-20 max-h-24 max-h-28 max-h-32 max-h-36 max-h-40 max-h-44 max-h-48 max-h-52 max-h-56 max-h-60 max-h-64 max-h-72 max-h-80 max-h-96 max-h-none max-h-full max-h-screen max-h-min max-h-max max-h-fit x-h-56 max-h-60 max-h-64 max-h-72 max-h-80 max-h-96 max-h-none max-h-full max-h-screen max-h-min max-h-max max-h-fit max-h-[30px]
}


// background color
// no escaping =  bg-((inherit|current|transparent|black|white|\[[\S]*\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))
// escaping for C++ = bg-((inherit|current|transparent|black|white|\\[[\\S]*\\])|(slate|gray|zinc|neutral|stone|red|orange|amber|yellow|lime|green|emerald|teal|cyan|sky|blue|indigo|violet|purple|fuchsia|pink|rose)-(950|900|800|700|600|500|400|300|200|150|100|50)?\\/(100|95|90|85|80|75|70|65|60|55|50|45|40|35|30|25|20|15|10|5|0))

// bg-inherit bg-current bg-transparent bg-black bg-white bg-[#12345]

// bg-slate-50/5 bg-slate-100/10 bg-slate-200/15 bg-slate-300/20 bg-slate-400/25 bg-slate-500/30 bg-slate-600/35 bg-slate-700/40 bg-slate-800/45 bg-slate-900/50 bg-slate-950/55 bg-slate-50/60

// bg-gray-50/5 bg-gray-100/10 bg-gray-200/15 bg-gray-300/20 bg-gray-400/25 bg-gray-500/30 bg-gray-600/35 bg-gray-700/40 bg-gray-800/45 bg-gray-900/50 bg-gray-950/55 bg-gray-50/60

// bg-zinc-50/5 bg-zinc-100/10 bg-zinc-200/15 bg-zinc-300/20 bg-zinc-400/25 bg-zinc-500/30 bg-zinc-600/35 bg-zinc-700/40 bg-zinc-800/45 bg-zinc-900/50 bg-zinc-950/55 bg-zinc-50/60

// bg-neutral-50/5 bg-neutral-100/10 bg-neutral-200/15 bg-neutral-300/20 bg-neutral-400/25 bg-neutral-500/30 bg-neutral-600/35 bg-neutral-700/40 bg-neutral-800/45 bg-neutral-900/50 bg-neutral-950/55 bg-neutral-50/60

// bg-stone-50/5 bg-stone-100/10 bg-stone-200/15 bg-stone-300/20 bg-stone-400/25 bg-stone-500/30 bg-stone-600/35 bg-stone-700/40 bg-stone-800/45 bg-stone-900/50 bg-stone-950/55 bg-stone-50/60

// bg-red-50/5 bg-red-100/10 bg-red-200/15 bg-red-300/20 bg-red-400/25 bg-red-500/30 bg-red-600/35 bg-red-700/40 bg-red-800/45 bg-red-900/50 bg-red-950/55 bg-red-50/60

// bg-orange-50/5 bg-orange-100/10 bg-orange-200/15 bg-orange-300/20 bg-orange-400/25 bg-orange-500/30 bg-orange-600/35 bg-orange-700/40 bg-orange-800/45 bg-orange-900/50 bg-orange-950/55 bg-orange-50/60

// bg-amber-50/5 bg-amber-100/10 bg-amber-200/15 bg-amber-300/20 bg-amber-400/25 bg-amber-500/30 bg-amber-600/35 bg-amber-700/40 bg-amber-800/45 bg-amber-900/50 bg-amber-950/55 bg-amber-50/60

// bg-yellow-50/5 bg-yellow-100/10 bg-yellow-200/15 bg-yellow-300/20 bg-yellow-400/25 bg-yellow-500/30 bg-yellow-600/35 bg-yellow-700/40 bg-yellow-800/45 bg-yellow-900/50 bg-yellow-950/55 bg-yellow-50/60

// bg-lime-50/5 bg-lime-100/10 bg-lime-200/15 bg-lime-300/20 bg-lime-400/25 bg-lime-500/30 bg-lime-600/35 bg-lime-700/40 bg-lime-800/45 bg-lime-900/50 bg-lime-950/55 bg-lime-50/60

// bg-green-50/5 bg-green-100/10 bg-green-200/15 bg-green-300/20 bg-green-400/25 bg-green-500/30 bg-green-600/35 bg-green-700/40 bg-green-800/45 bg-green-900/50 bg-green-950/55 bg-green-50/60

// bg-emerald-50/5 bg-emerald-100/10 bg-emerald-200/15 bg-emerald-300/20 bg-emerald-400/25 bg-emerald-500/30 bg-emerald-600/35 bg-emerald-700/40 bg-emerald-800/45 bg-emerald-900/50 bg-emerald-950/55 bg-emerald-50/60

// bg-teal-50/5 bg-teal-100/10 bg-teal-200/15 bg-teal-300/20 bg-teal-400/25 bg-teal-500/30 bg-teal-600/35 bg-teal-700/40 bg-teal-800/45 bg-teal-900/50 bg-teal-950/55 bg-teal-50/60

// bg-cyan-50/5 bg-cyan-100/10 bg-cyan-200/15 bg-cyan-300/20 bg-cyan-400/25 bg-cyan-500/30 bg-cyan-600/35 bg-cyan-700/40 bg-cyan-800/45 bg-cyan-900/50 bg-cyan-950/55 bg-cyan-50/60

// bg-sky-50/5 bg-sky-100/10 bg-sky-200/15 bg-sky-300/20 bg-sky-400/25 bg-sky-500/30 bg-sky-600/35 bg-sky-700/40 bg-sky-800/45 bg-sky-900/50 bg-sky-950/55 bg-sky-50/60

// bg-blue-50/5 bg-blue-100/10 bg-blue-200/15 bg-blue-300/20 bg-blue-400/25 bg-blue-500/30 bg-blue-600/35 bg-blue-700/40 bg-blue-800/45 bg-blue-900/50 bg-blue-950/55 bg-blue-50/60

// bg-indigo-50/5 bg-indigo-100/10 bg-indigo-200/15 bg-indigo-300/20 bg-indigo-400/25 bg-indigo-500/30 bg-indigo-600/35 bg-indigo-700/40 bg-indigo-800/45 bg-indigo-900/50 bg-indigo-950/55 bg-indigo-50/60

// bg-violet-50/5 bg-violet-100/10 bg-violet-200/15 bg-violet-300/20 bg-violet-400/25 bg-violet-500/30 bg-violet-600/35 bg-violet-700/40 bg-violet-800/45 bg-violet-900/50 bg-violet-950/55 bg-violet-50/60

// bg-purple-50/5 bg-purple-100/10 bg-purple-200/15 bg-purple-300/20 bg-purple-400/25 bg-purple-500/30 bg-purple-600/35 bg-purple-700/40 bg-purple-800/45 bg-purple-900/50 bg-purple-950/55 bg-purple-50/60

// bg-fuchsia-50/5 bg-fuchsia-100/10 bg-fuchsia-200/15 bg-fuchsia-300/20 bg-fuchsia-400/25 bg-fuchsia-500/30 bg-fuchsia-600/35 bg-fuchsia-700/40 bg-fuchsia-800/45 bg-fuchsia-900/50 bg-fuchsia-950/55 bg-fuchsia-50/60

// bg-pink-50/5 bg-pink-100/10 bg-pink-200/15 bg-pink-300/20 bg-pink-400/25 bg-pink-500/30 bg-pink-600/35 bg-pink-700/40 bg-pink-800/45 bg-pink-900/50 bg-pink-950/55 bg-pink-50/60

// bg-rose-50/5 bg-rose-100/10 bg-rose-200/15 bg-rose-300/20 bg-rose-400/25 bg-rose-500/30 bg-rose-600/35 bg-rose-700/40 bg-rose-800/45 bg-rose-900/50 bg-rose-950/55 bg-rose-50/60

