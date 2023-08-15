#include "crow/crow.h"
#include "libreoffice_service.hpp"
#include "logger.hpp"
#include "fmt/format.h"
#include "utility.hpp"
#include "prim_exception.hpp"

// fordec
void setRouting(crow::SimpleApp& app);
//

static Logger logger;

int main(int argc, char* argv[])
{
    crow::SimpleApp crowApp;

    setRouting(crowApp);

    crowApp.loglevel(crow::LogLevel::Debug);
    crowApp.port(8080).multithreaded().run();

    return 0;
}

void setRouting(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/api/convert")
        .methods("POST"_method)
    ([](const crow::request& req){
        if(req.body.length() == 0u) return crow::response(400, "Body of the request must contain document data.");

        char* fromFormatStr = req.url_params.get("fromFormat");
        char* toFormatStr = req.url_params.get("toFormat");
        if(fromFormatStr == nullptr || toFormatStr == nullptr) return crow::response(400, "Invalid url parameters.");

        FileFormat fromFormat = FileFormat::parse(toLower(fromFormatStr));
        FileFormat toFormat = FileFormat::parse(toLower(toFormatStr));
        if(fromFormat == FileFormat::NOT_DEFINED || toFormat == FileFormat::NOT_DEFINED) 
            return crow::response(400, "Invalid 'from' or 'to' format.");
        
        LibreOfficeService libreService;
        std::string convertedData;
        try
        {
            convertedData = libreService.convert(req.body, fromFormat, toFormat);
        }
        catch(prim::Exception ex)
        {
            std::string message = fmt::format("Failed to convert document: {}", ex.what());
            logger.logError(message);
            return crow::response(crow::status::INTERNAL_SERVER_ERROR, message);
        }

        crow::response response(crow::status::OK, convertedData);
        response.set_header("Content-type", toFormat.mimeType);
        return response;
    });
}
