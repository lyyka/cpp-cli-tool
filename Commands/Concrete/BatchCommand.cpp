//
// Created by Luka Robajac on 10. 1. 2026..
//

#include "BatchCommand.h"

#include "../../Core/Interpreter.h"
#include "../../Core/Reader/FileReader.h"

BatchCommand::BatchCommand(Outputter* outputStream, std::vector<Argument*> argument, std::vector<Argument*> opts, std::ostream& errorOutputStream)
    :Command(outputStream, std::move(argument), std::move(opts), errorOutputStream)
{
}

unsigned int BatchCommand::minArgumentsCount() const
{
    return 1;
}

unsigned int BatchCommand::maxArgumentsCount() const
{
    return 1;
}

bool BatchCommand::expectsOutput() const
{
    return true;
}

void BatchCommand::handle(Interpreter* interpreter) const
{
    const std::string filename = this->argument.at(0)->getToken()->getToken();

    /*
     * todo: here is the list:
     *  - Садржај улазног фајла са задатим именом интерпретира као произвољно дуг низ
        командних линија раздвојених знаком за нови ред и интерпретира све те командне линије
        као што је описано у овом документу, исто као да су оне учитане са конзоле (тзв. пакетна
        обрада, енгл. batch). Интерпретира независно једну по једну командну линију све док не
        наиђе на крај улазног фајла. Свака команда којој није задат аргумент, осим оних које нису
        првонаведене у цевоводу, преко конзоле учитава потребни аргумент након чега се
        наставља извршавање преосталих команди. Подразумевани излазни токови команди
        одговарају излазном току команде batch, али команде могу да дефинишу редирекције
        излазних токова на појединачном нивоу. Уколико је нека командна линија изазвала
        грешку, исписује њену поруку о грешци на свој излазни ток грешке и наставља даље на
        следећу. Улазни фајл може садржати било које команде, па и саму команду batch;
        рекурзију не треба спречавати, последице њеног извшравања су одговорност корисника.
     */
    auto* i = new Interpreter(' ', new FileReader(filename), new Parser(this->outputStream));
    i->run();
    delete i;

    this->outputStream->output("\n");
}

bool BatchCommand::validate() const
{
    if (this->argument.empty())
    {
        this->errorOutputStream << "BatchCommand: Argument is required!" << std::endl;
        return false;
    }

    if (this->argument.size() > 1)
    {
        this->errorOutputStream << "BatchCommand: Only 1 argument is supported!" << std::endl;
        return false;
    }

    return true;
}