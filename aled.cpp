void sync(uqac::serialisation::Deserializer deser, uqac::replication::LinkingContext context)
{
    uint32_t testFin = deser.Deserialize<uint32_t>();
    while (testFin != 0) // Test pas bon du tout pour l'instant, mais par défaut je fais ça
    {
        // ALED jsp comment faire appel à la classe NetworkId qui est définie avec le using dans LinkingContext.h
        // -> EDIT : j'ai l'impression qu'il y a même pas besoin de cast du coup
        // NetworkId idObjet = static_cast<NetworkId>(testFin);
        uint32_t idClass = deser.Deserialize<uint32_t>();

        auto option = context.LinkedObj(testFin);
        if (option.has_value()) {
            std::cerr << "Error : No object found with id in LinkingContext" << std::endl; // print l'id ?
            exit(1);
        }
        
        switch (idClass)
        {
            // Les casts que je fais là fonctionnent pas, donc il faudra peut être faire une méthode templatée, mais jsp comment faire
            case 'PLAY':
                uqac::game::Player play = static_cast<uqac::game::Player>(*option.value());
                play.Read(&deser);
                break;
            case 'ENEM':
                uqac::game::Enemy enem = static_cast<uqac::game::Enemy>(*option.value());
                enem.Read(&deser);
                break;
        }

        testFin = deser.Deserialize<uint32_t>();
    }
}