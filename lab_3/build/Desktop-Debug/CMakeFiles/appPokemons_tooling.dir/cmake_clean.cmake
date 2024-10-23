file(REMOVE_RECURSE
  "Pokemons/Main.qml"
  "Pokemons/images/faq.gif"
  "Pokemons/images/pikachu.gif"
  "Pokemons/images/pikachu.png"
  "Pokemons/images/question.gif"
  "Pokemons/images/search.svg"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/appPokemons_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
